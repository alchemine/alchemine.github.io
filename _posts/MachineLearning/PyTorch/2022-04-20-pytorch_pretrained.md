---
title: Using pretrained classification model (PyTorch)
tags: PyTorch
---

<!--more-->

# 1. Load packages

## 1) Common packages


```python
import os
from os.path import join, abspath, dirname
from tqdm import tqdm
import random

import numpy as np
import pandas as pd
from dask import delayed, compute
from dask.diagnostics import ProgressBar
import sklearn
import cv2
```

## 2) PyTorch packages


```python
import torch
from torch.utils.data import Dataset, DataLoader
from torchvision import transforms

device = torch.device('cuda')
```

## 3) Parameters


```python
class PATH:
    root   = abspath(dirname('../'))
    input  = join(root, 'open')
    train  = join(input, 'train')
    test   = join(input, 'test')

TEST_SIZE    = 0.3
LABEL        = 'label'
SIZE         = 128
INPUT_SHAPE  = (SIZE, SIZE, 3)
BATCH_SIZE   = 32

RANDOM_STATE = 42
def seed_everything(seed):
    random.seed(seed)
    np.random.seed(seed)
    sklearn.random.seed(RANDOM_STATE)
    os.environ["PYTHONHASHSEED"] = str(seed)
    torch.manual_seed(seed)
    torch.cuda.manual_seed(seed)  # type: ignore
    torch.backends.cudnn.deterministic = True  # type: ignore
    torch.backends.cudnn.benchmark = True  # type: ignore
seed_everything(RANDOM_STATE)
```

# 2. Load dataset


```python
from sklearn.model_selection import train_test_split
from sklearn.preprocessing import LabelEncoder

@delayed
def load_image(path, size):
    return cv2.resize(cv2.imread(path), (size, size)) / 255

train_full_data_meta = pd.read_csv(join(PATH.input, 'train_df.csv'), index_col=0)
train_data_meta, val_data_meta = train_test_split(train_full_data_meta, test_size=TEST_SIZE, stratify=train_full_data_meta[LABEL])
test_data_meta       = pd.read_csv(join(PATH.input, 'test_df.csv'), index_col=0)

with ProgressBar():
    X_train = np.array(compute(*[load_image(join(PATH.train, name), SIZE) for name in train_data_meta['file_name']]))
    X_val   = np.array(compute(*[load_image(join(PATH.train, name), SIZE) for name in val_data_meta['file_name']]))
    X_test  = np.array(compute(*[load_image(join(PATH.test, name), SIZE) for name in test_data_meta['file_name']]))

y_enc   = LabelEncoder()
y_train = y_enc.fit_transform(train_data_meta['label'])
y_val   = y_enc.transform(val_data_meta['label'])

N_CLASSES = len(y_enc.classes_)
```

    [########################################] | 100% Completed |  5.4s
    [########################################] | 100% Completed |  2.2s
    [########################################] | 100% Completed |  3.6s



```python
class CustomDataset(Dataset):
    def __init__(self, X, y=None, transform=None):
        self.X = X.astype(np.float32)
        self.y = y.astype(np.long) if y is not None else y
        self.transform = transform
    def __len__(self):
        return len(self.X)
    def __getitem__(self, idx):
        X = self.transform(self.X[idx])
        return X if self.y is None else (X, self.y[idx])

def generate_dataloader(X, y=None, batch_size=32, shuffle=False):
    MEAN_TRAIN = [0.485, 0.456, 0.406]
    STD_TRAIN  = [0.229, 0.224, 0.225]
    ds = CustomDataset(X, y, transform=transforms.Compose([
        transforms.ToTensor(),
        transforms.Normalize(mean=MEAN_TRAIN, std=STD_TRAIN)
    ]))
    dl = DataLoader(ds, batch_size=batch_size, shuffle=shuffle, num_workers=os.cpu_count(), pin_memory=True)
    return dl
```


```python
%%time

dl_train = generate_dataloader(X_train, y_train, batch_size=BATCH_SIZE, shuffle=True)
dl_val   = generate_dataloader(X_val, y_val, batch_size=BATCH_SIZE)
dl_test  = generate_dataloader(X_test, batch_size=1)
```

    CPU times: user 508 ms, sys: 684 ms, total: 1.19 s
    Wall time: 1.19 s


# 3. Training

## 1) Fix pretrained model


```python
import pytorch_lightning as pl
import timm
from torch import nn
import torch.nn.functional as F
from sklearn.metrics import f1_score

class Model(pl.LightningModule):
    def __init__(self, n_classes):
        super().__init__()
        self.model = timm.create_model('efficientnet_b0', pretrained=True, num_classes=n_classes)
    def forward(self, x):
        return self.model(x)
    def freeze(self):
        for param in self.model.parameters():
            param.requires_grad = False
        for param in self.model.classifier.parameters():
            param.requires_grad = True
    def unfreeze(self):
        for param in self.model.parameters():
            param.requires_grad = True
    def configure_optimizers(self):
        return torch.optim.Adam(self.model.classifier.parameters(), lr=2e-3)
    def step(self, batch):
        X, y = batch
        pred = self(X)
        loss = F.cross_entropy(pred, y)
        return loss, y, pred
    def training_step(self, batch, batch_idx):
        loss, y, pred = self.step(batch)
        return {'loss': loss}
    def validation_step(self, batch, batch_idx):
        loss, y, pred = self.step(batch)
        self.log('val_loss', loss)
        return {'loss': loss, 'y': y.detach(), 'pred': pred.detach()}
    def validation_epoch_end(self, outputs):
        avg_loss = torch.stack([x['loss'] for x in outputs]).mean()
        return {'loss': avg_loss}
    def predict_step(self, batch, batch_idx, dataloader_idx=None):
        X = batch
        return int(torch.argmax(self(X), dim=1).cpu().numpy())
```


```python
from pytorch_lightning.callbacks.early_stopping import EarlyStopping

model = Model(N_CLASSES)
model.freeze()
trainer = pl.Trainer(callbacks=[EarlyStopping(monitor='val_loss', patience=5)], gpus=1, max_epochs=5)
H = trainer.fit(model, dl_train, dl_val)
```

    GPU available: True, used: True
    TPU available: False, using: 0 TPU cores
    LOCAL_RANK: 0 - CUDA_VISIBLE_DEVICES: [0,1,2]

      | Name  | Type         | Params
    ---------------------------------------
    0 | model | EfficientNet | 4.1 M
    ---------------------------------------
    112 K     Trainable params
    4.0 M     Non-trainable params
    4.1 M     Total params
    16.481    Total estimated model params size (MB)

    Validation sanity check: 0it [00:00, ?it/s]
    Training: 0it [00:00, ?it/s]
    Validating: 0it [00:00, ?it/s]

## 2) Fine-tuning


```python
model.unfreeze()
trainer = pl.Trainer(callbacks=[EarlyStopping(monitor='val_loss', patience=5)], gpus=1, max_epochs=10)
H = trainer.fit(model, dl_train, dl_val)
```

    GPU available: True, used: True
    TPU available: False, using: 0 TPU cores
    LOCAL_RANK: 0 - CUDA_VISIBLE_DEVICES: [0,1,2]

      | Name  | Type         | Params
    ---------------------------------------
    0 | model | EfficientNet | 4.1 M
    ---------------------------------------
    4.1 M     Trainable params
    0         Non-trainable params
    4.1 M     Total params
    16.481    Total estimated model params size (MB)

    Validation sanity check: 0it [00:00, ?it/s]
    Training: 0it [00:00, ?it/s]
    Validating: 0it [00:00, ?it/s]


# 4. Inference


```python
pred_test = trainer.predict(model, dl_test)
pred_test = y_enc.inverse_transform(pred_test)
pred_test.shape
```

    LOCAL_RANK: 0 - CUDA_VISIBLE_DEVICES: [0,1,2]
    Predicting: 94it [00:00, ?it/s]
    (2154,)
