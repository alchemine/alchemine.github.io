---
title: Max-norm Regularization
tags: MachineLearning_Base
aside:
  toc: true
---

# Remarks
본 포스팅은 **Hands-On Machine Learning with Scikit-Learn & TensorFlow ([Auérlien Géron](https://github.com/ageron/handson-ml), [박해선(역)](https://github.com/rickiepark/handson-ml), 한빛미디어)** 등을 참고하여 작성되었습니다.

<!--more-->
---

**Max-norm Regularization** \
$ \| W \|_2 \leq r$ constraint를 사용하는 regularization
{:.success}

1. 일반적으로 $r=1$ 을 사용하나, 작은 값을 사용할수록 regularization의 양이 증가하여 overfitting을 방지하는 효과를 낸다.
2. 일반적으로, \
MLP: 각 neuron의 weight vector에 독립적으로 적용(`axis=0`, default) \
CNN: 각 channel축에 대해 독립적으로 적용(`axis=[0, 1, 2]`)


```
keras.layers.Dense(.., kernel_constraint=keras.constraints.max_norm(1.))
```
