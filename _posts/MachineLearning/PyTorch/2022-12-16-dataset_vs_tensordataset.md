---
title: torch.utils.data.Dataset vs TensorDataset
tags: PyTorch
---

<!--more-->

# 1. `torch.utils.data.TensorDataset`
첫 번째 차원(batch size)이 동일한 tensor들을 wrapping하는 dataset

{% highlight python linenos %}
from torch.utils.data import TensorDataset

X_train = torch.FloatTensor([[73, 80, 75],
                             [93, 88, 93],
                             [89, 91, 90],
                             [96, 98, 100],
                             [73, 66, 70]])
y_train = torch.FloatTensor([[152], [185], [180], [196], [142]])
ds = TensorDataset(X_train, y_train)
{% endhighlight %}


# 2. `torch.utils.data.Dataset`
Custom dataset을 만드는데 사용되는 abstract class

{% highlight python linenos %}
from torch.utils.data import Dataset

class CustomDataset(Dataset):
  def __init__(self, *args, **kwargs):
    super().__init__(*args, **kwargs)
    ...

  def __getitem__(self, idx):
    return ...

  def __len__(self):
    return ...

ds = CustomDataset(X_train, y_train)
{% endhighlight %}


# Reference
- [difference between Dataset and TensorDataset in pyTorch](https://stackoverflow.com/questions/67683406/difference-between-dataset-and-tensordataset-in-pytorch)
- [https://pytorch.org/docs/stable/_modules/torch/utils/data/dataset.html#TensorDataset](https://pytorch.org/docs/stable/_modules/torch/utils/data/dataset.html#TensorDataset)
