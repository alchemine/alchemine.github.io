---
title: F.cross_entropy()
tags: PyTorch
---

<!--more-->

{% highlight python linenos %}
logits = torch.rand(3, 5)
logits
{% endhighlight %}

    tensor([[0.7874, 0.5352, 0.7366, 0.2296, 0.8006],
            [0.2526, 0.0581, 0.6675, 0.7737, 0.9956],
            [0.4477, 0.9810, 0.8212, 0.2520, 0.1143]])

{% highlight python linenos %}
labels    = torch.tensor([2, 4, 3])
labels_oh = torch.zeros(3, 5).scatter(1, labels.unsqueeze(-1), 1)
labels_oh
{% endhighlight %}

    tensor([[0., 0., 1., 0., 0.],
            [0., 0., 0., 0., 1.],
            [0., 0., 0., 1., 0.]])


$CEE(y, \hat y) = -\frac{1}{n} \sum_i \sum_c y_i^{(c)} log \ \hat y_i^{(c)}$
1. `logits`: Value before softmax ($= XW$)
2. `F.log_softmax()`: $log \ \hat y_i^{(c)}$


{% highlight python linenos %}
loss = -(labels_oh * torch.log(F.softmax(logits, dim=1))).sum(1).mean()
loss
{% endhighlight %}

    tensor(1.5561)

{% highlight python linenos %}
assert loss == F.nll_loss(F.log_softmax(logits, dim=1), labels) \
            == F.cross_entropy(logits, labels)
{% endhighlight %}
