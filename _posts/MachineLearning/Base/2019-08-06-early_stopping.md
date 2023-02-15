---
layout: article
title: Early stopping
tags: MachineLearning_Base
sidebar:
  nav: docs-en
---

**Early stopping**은 iterative algorithm에서 사용할 수 있는 regularization 방법으로 validation error가 최솟값에 도달하였다고 판단되면 바로 학습을 중지하는 방법입니다.
{:.success}

<!--more-->

# Remarks
본 포스팅은 **Hands-On Machine Learning with Scikit-Learn & TensorFlow ([Auérlien Géron](https://github.com/ageron/handson-ml), [박해선(역)](https://github.com/rickiepark/handson-ml), 한빛미디어)** 를 기반으로 작성되었습니다.

---

Epoch에 따른 error 그래프를 그려보면 일반적으로 다음과 같은 형태를 보이게 됩니다. <br>

![Image](https://raw.githubusercontent.com/alchemine/alchemine.github.io/master/_posts/assets/es_1.jpg){:.border} <br>

{% highlight python linenos %}

poly_scaler = Pipeline([
    ('poly_features', PolynomialFeatures(degree=10, include_bias=False)),
    ('std_scaler', StandardScaler())
])
X_poly_scaled = poly_scaler.fit_transform(X)

sgd_reg = SGDRegressor(max_iter=1000, penalty=None, learning_rate='constant', eta0=0.0005, early_stopping=True)
sgd_reg.fit(X_poly_scaled, y)

{% endhighlight %}
