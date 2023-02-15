---
title: Random State in TensorFlow
tags: TensorFlow
aside:
  toc: true
---

<!--more-->

{% highlight python linenos %}
import os
import tensorflow as tf
from tfdeterminism import patch

RANDOM_STATE = 42

patch()
os.environ['PYTHONHASHSEED"]         = str(RANDOM_STATE)
os.environ['TF_DETERMINISTIC_OPS']   = '1'
os.environ['TF_CUDNN_DETERMINISTIC'] = '1'
tf.keras.utils.set_random_seed(RANDOM_STATE)
{% endhighlight %}

`tf.keras.utils.set_random_seed(RANDOM_STATE)` 는 다음과 같은 코드들을 실행한다.

{% highlight python linenos %}
import random
import numpy as np
import tensorflow as tf

random.seed(seed)
np.random.seed(seed)
tf.random.set_seed(seed)
{% endhighlight %}
