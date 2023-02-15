---
title: Using pretrained classification model (TensorFlow)
tags: TensorFlow
aside:
  toc: true
---

<!--more-->

# 1. Load packages

## 1) Common packages


```python
import os
from os.path import join, abspath, dirname
from tqdm import tqdm

import numpy as np
import pandas as pd
from dask import delayed, compute
from dask.diagnostics import ProgressBar
import sklearn
import cv2
```

## 2) TensorFlow packages


```python
import tensorflow as tf
from tensorflow import keras
import tensorflow_addons as tfa

for gpu in tf.config.experimental.list_physical_devices('GPU'):
    tf.config.experimental.set_memory_growth(gpu, True)
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
np.random.seed(RANDOM_STATE)
tf.random.set_seed(RANDOM_STATE)
sklearn.random.seed(RANDOM_STATE)
```

# 2. Load dataset


```python
from sklearn.model_selection import train_test_split
from sklearn.preprocessing import OneHotEncoder

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

y_enc   = OneHotEncoder(sparse=False)
y_train = y_enc.fit_transform(train_data_meta[['label']])
y_val   = y_enc.transform(val_data_meta[['label']])

N_CLASSES = len(y_enc.categories_[0])
```

    [########################################] | 100% Completed |  5.3s
    [########################################] | 100% Completed |  2.1s
    [########################################] | 100% Completed |  3.5s



```python
def generate_dataset(X, y=None, batch_size=32):
    MEAN_TRAIN = [0.485, 0.456, 0.406]
    STD_TRAIN  = [0.229, 0.224, 0.225]
    normalize  = lambda X, y=None: ((X-MEAN_TRAIN)/STD_TRAIN, y)
    if y is None:
        ds = tf.data.Dataset.from_tensor_slices(X)
    else:
        ds = tf.data.Dataset.from_tensor_slices((X, y)).shuffle(buffer_size=1000)
    return ds.batch(batch_size).map(normalize, num_parallel_calls=tf.data.AUTOTUNE).cache().prefetch(tf.data.AUTOTUNE)
```


```python
%%time

ds_train = generate_dataset(X_train, y_train, batch_size=BATCH_SIZE)
ds_val   = generate_dataset(X_val, y_val, batch_size=BATCH_SIZE)
ds_test  = generate_dataset(X_test, batch_size=BATCH_SIZE)
```

    CPU times: user 6.68 s, sys: 5.6 s, total: 12.3 s
    Wall time: 12.9 s


# 3. Training

## 1) Fix pretrained model


```python
base_model = keras.applications.EfficientNetB0(include_top=False, input_shape=INPUT_SHAPE)
base_model.trainable = False

inputs  = keras.layers.Input(INPUT_SHAPE)
hidden  = base_model(inputs, training=False)
hidden  = keras.layers.GlobalAveragePooling2D()(hidden)
outputs = keras.layers.Dense(N_CLASSES, activation='softmax')(hidden)
model   = keras.Model(inputs, outputs)
model.compile(optimizer=keras.optimizers.Adam(2e-3), loss='categorical_crossentropy', metrics=[tfa.metrics.F1Score(num_classes=N_CLASSES, average='macro'), 'accuracy'])
model.summary()
```

    Model: "model_1"
    _________________________________________________________________
    Layer (type)                 Output Shape              Param #
    =================================================================
    input_4 (InputLayer)         [(None, 128, 128, 3)]     0
    _________________________________________________________________
    efficientnetb0 (Functional)  (None, 4, 4, 1280)        4049571
    _________________________________________________________________
    global_average_pooling2d_1 ( (None, 1280)              0
    _________________________________________________________________
    dense_1 (Dense)              (None, 88)                112728
    =================================================================
    Total params: 4,162,299
    Trainable params: 112,728
    Non-trainable params: 4,049,571
    _________________________________________________________________



```python
from tensorflow.keras.callbacks import EarlyStopping

H = model.fit(ds_train, validation_data=ds_val, epochs=5, callbacks=[EarlyStopping(patience=5, restore_best_weights=True)])
```

    Epoch 1/5
    94/94 [==============================] - 12s 89ms/step - loss: 3.1952 - f1_score: 0.0196 - accuracy: 0.1627 - val_loss: 2.8756 - val_f1_score: 0.0133 - val_accuracy: 0.1526
    Epoch 2/5
    94/94 [==============================] - 7s 76ms/step - loss: 2.8180 - f1_score: 0.0373 - accuracy: 0.2693 - val_loss: 2.6708 - val_f1_score: 0.0389 - val_accuracy: 0.2967
    Epoch 3/5
    94/94 [==============================] - 7s 76ms/step - loss: 2.6575 - f1_score: 0.0525 - accuracy: 0.3425 - val_loss: 2.5371 - val_f1_score: 0.0553 - val_accuracy: 0.3684
    Epoch 4/5
    94/94 [==============================] - 8s 83ms/step - loss: 2.5429 - f1_score: 0.0621 - accuracy: 0.3939 - val_loss: 2.4350 - val_f1_score: 0.0604 - val_accuracy: 0.4011
    Epoch 5/5
    94/94 [==============================] - 7s 76ms/step - loss: 2.4522 - f1_score: 0.0694 - accuracy: 0.4347 - val_loss: 2.3517 - val_f1_score: 0.0632 - val_accuracy: 0.4174


## 2) Fine-tuning


```python
base_model.trainable = True
model.compile(optimizer=keras.optimizers.Adam(2e-4), loss='categorical_crossentropy', metrics=[tfa.metrics.F1Score(num_classes=N_CLASSES, average='macro'), 'accuracy'])
H = model.fit(ds_train, validation_data=ds_val, epochs=5, callbacks=[EarlyStopping(patience=5, restore_best_weights=True)])
```

    Epoch 1/5
    94/94 [==============================] - 53s 363ms/step - loss: 3.7166 - f1_score: 0.0079 - accuracy: 0.0845 - val_loss: 3.2655 - val_f1_score: 0.0071 - val_accuracy: 0.0911
    Epoch 2/5
    94/94 [==============================] - 20s 218ms/step - loss: 3.1042 - f1_score: 0.0171 - accuracy: 0.1554 - val_loss: 2.4854 - val_f1_score: 0.0504 - val_accuracy: 0.3777
    Epoch 3/5
    94/94 [==============================] - 21s 225ms/step - loss: 1.7701 - f1_score: 0.0972 - accuracy: 0.5376 - val_loss: 1.1653 - val_f1_score: 0.1392 - val_accuracy: 0.7204
    Epoch 4/5
    94/94 [==============================] - 20s 217ms/step - loss: 1.2021 - f1_score: 0.1356 - accuracy: 0.6990 - val_loss: 1.0036 - val_f1_score: 0.1489 - val_accuracy: 0.7282
    Epoch 5/5
    94/94 [==============================] - 20s 216ms/step - loss: 1.0728 - f1_score: 0.1423 - accuracy: 0.7287 - val_loss: 0.9888 - val_f1_score: 0.1524 - val_accuracy: 0.7235


# 4. Inference


```python
pred_test = model.predict(ds_test)
pred_test = y_enc.inverse_transform(pred_test)
pred_test.shape
```




    (2154, 1)
