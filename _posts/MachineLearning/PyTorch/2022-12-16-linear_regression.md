---
title: Linear Regression
tags: PyTorch
aside:
  toc: true
---

<!--more-->

# 1. Load Packages
{% highlight python linenos %}
import torch
from torch import nn, optim
import torch.nn.functional as F

torch.manual_seed(1)
{% endhighlight %}


# 2. Prepare Dataset
{% highlight python linenos %}
X_train = torch.FloatTensor([[73,  80,  75],
                             [93,  88,  93],
                             [89,  91,  80],
                             [96,  98,  100],
                             [73,  66,  70]])
y_train = torch.FloatTensor([[152],  [185],  [180],  [196],  [142]])
{% endhighlight %}


# 1) Without Using `torch.nn` module
# 3. Initialize Weights
{% highlight python linenos %}
W = torch.ones((3, 1), requires_grad=True)
b = torch.zeros(1, requires_grad=True)
{% endhighlight %}


# 4. Gradient Descent
{% highlight python linenos %}
params = [W, b]
optimizer = optim.SGD(params, lr=1e-5)

for epoch in range(10):
    # 1) hypothesis 정의
    hypothesis = X_train @ W + b

    # 2) cost 정의
    cost = torch.mean((hypothesis - y_train)**2)

    # 3) optimizer 설정
    optimizer.zero_grad()  # gradient를 0으로 초기화
    cost.backward()        # gradient 계산
    optimizer.step()       # W, b 업데이트

    print(f"Epoch {epoch:2}/100 | Cost: {cost.item():.4f}")
{% endhighlight %}


# 2) Using `torch.nn` module
# 3. Gradient Descent
{% highlight python linenos %}
model     = nn.LazyLinear(1, bias=True)
optimizer = optim.SGD(model.parameters(), lr=1e-5)

for epoch in range(10):
    # 1) hypothesis 정의
    hypothesis = model(X_train)

    # 2) cost 정의
    cost = F.mse_loss(hypothesis, y_train)

    # 3) optimizer 설정
    optimizer.zero_grad()  # gradient를 0으로 초기화
    cost.backward()        # gradient 계산
    optimizer.step()       # W, b 업데이트

    print(f"Epoch {epoch:>2}/100 | Cost: {cost.item():.4f}")
{% endhighlight %}


# 3) Using `torch.nn` module - Subclass API
# 3. Gradient Descent
{% highlight python linenos %}
class Model(nn.Module):
    def __init__(self, output_dim):
        super().__init__()
        self.linear = nn.LazyLinear(output_dim)

    def forward(self, x):
        return self.linear(x)


model     = Model(3)
optimizer = optim.SGD(model.parameters(), lr=1e-5)

for epoch in range(10):
    # 1) hypothesis 정의
    hypothesis = model(X_train)

    # 2) cost 정의
    cost = F.mse_loss(hypothesis, y_train)

    # 3) optimizer 설정
    optimizer.zero_grad()  # gradient를 0으로 초기화
    cost.backward()        # gradient 계산
    optimizer.step()       # W, b 업데이트

    print(f"Epoch {epoch:>2}/100 | Cost: {cost.item():.4f}")
{% endhighlight %}
