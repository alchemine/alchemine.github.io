---
title: Logistic Regression Example
tags: PyTorch
---

<!--more-->

# 1. Import Packages
{% highlight python linenos %}
#!pip install seaborn livelossplot torchsummary torchmetrics

from tqdm import tqdm
from livelossplot import PlotLosses

import torch
from torch import nn
import torch.nn.functional as F
from torch.utils.data import Dataset, DataLoader
from torchsummary import summary as summary_
import torchvision as tv
from torchvision import transforms
import torchmetrics as tm

def set_random_seed_torch(seed):
    torch.manual_seed(seed)
    torch.cuda.manual_seed(seed)
    torch.backends.cudnn.deterministic = True
    torch.backends.cudnn.benchmark = True

SEED = 42
set_random_seed_torch(SEED)

device = torch.device("cuda:0" if torch.cuda.is_available() else "cpu")
cuda   = lambda *xs: (x.to(device) for x in xs)
{% endhighlight %}


# 2. Load Dataset
{% highlight python linenos %}
train_ds = tv.datasets.MNIST(root='data', download=True, train=True, transform=transforms.ToTensor())
test_ds  = tv.datasets.MNIST(root='data', download=True, train=False, transform=transforms.ToTensor())
train_dl = DataLoader(train_data, batch_size=32, shuffle=True, drop_last=True, pin_memory=True)
test_dl  = DataLoader(test_data, batch_size=32, shuffle=False, pin_memory=True)

INPUT_SHAPE  = (1, 28, 28)
OUTPUT_SHAPE = 1
N_CLASSES    = 10
{% endhighlight %}


# 3. Import Packages
{% highlight python linenos %}
FILTERS     = 32
KERNEL_SIZE = 3
UNITS       = 128


class MyModel(nn.Module):
    def __init__(self, filters, kernel_size, units, n_classes, input_shape):
        super().__init__()
        self.input_shape = input_shape
        self.conv1       = nn.LazyConv2d(filters, kernel_size)
        self.d1          = nn.LazyLinear(units)
        self.output      = nn.LazyLinear(n_classes)
    def forward(self, x):
        x = F.relu(self.conv1(x))
        x = x.flatten(start_dim=1)
        x = F.relu(self.d1(x))
        logits = self.output(x)
        return logits
    def summary(self):
        summary_(self, self.input_shape)


model     = cuda(MyModel(FILTERS, KERNEL_SIZE, UNITS, N_CLASSES, INPUT_SHAPE))
criterion = cuda(nn.CrossEntropyLoss())  # input: (logits, labels)
get_acc   = cuda(tm.Accuracy(task='multiclass', num_classes=N_CLASSES))
optimizer = torch.optim.Adam(model.parameters())  # to(device) 가 모두 완료된 이후에 정의
model.summary()
{% endhighlight %}

```
----------------------------------------------------------------
        Layer (type)               Output Shape         Param #
================================================================
            Conv2d-1           [-1, 32, 26, 26]             320
            Linear-2                  [-1, 128]       2,769,024
            Linear-3                   [-1, 10]           1,290
================================================================
Total params: 2,770,634
Trainable params: 2,770,634
Non-trainable params: 0
----------------------------------------------------------------
Input size (MB): 0.00
Forward/backward pass size (MB): 0.17
Params size (MB): 10.57
Estimated Total Size (MB): 10.74
----------------------------------------------------------------
```


# 4. Training
{% highlight python linenos %}
def train_step(images, labels):
    probs = model(images)
    loss  = criterion(probs, labels)
    acc   = get_acc(probs.argmax(1), labels)
    optimizer.zero_grad()
    loss.backward()
    optimizer.step()
    return loss, acc

def test_step(images, labels):
    probs = model(images)
    loss  = criterion(probs, labels)
    acc   = get_acc(probs.argmax(1), labels)
    return loss, acc

EPOCHS = 5
liveloss = PlotLosses()

rst = pd.DataFrame(columns=['loss', 'acc', 'val_loss', 'val_acc'], index=pd.Index([], name='Epoch'))
for epoch in tqdm(range(1, EPOCHS+1)):
    model.train()
    for images, labels in train_dl:
        images, labels = cuda(images, labels)
        loss, acc = train_step(images, labels)

    model.eval()
    with torch.no_grad():
        for test_images, test_labels in test_dl:
            test_images, test_labels = cuda(test_images, test_labels)
            val_loss, val_acc = test_step(test_images, test_labels)

    rst.loc[epoch] = [x.item() for x in (loss, acc, val_loss, val_acc)]
    liveloss.update(rst.loc[epoch])
    liveloss.send()
{% endhighlight %}

```
100%|██████████| 5/5 [00:31<00:00,  6.24s/it]
Accuracy
	training         	 (min:    1.000, max:    1.000, cur:    1.000)
	validation       	 (min:    1.000, max:    1.000, cur:    1.000)
Loss
	training         	 (min:    0.000, max:    0.004, cur:    0.000)
	validation       	 (min:    0.000, max:    0.000, cur:    0.000)
```
