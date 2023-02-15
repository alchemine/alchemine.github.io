---
title: Ignore warnings
tags: Python
---

<!--more-->

# 1. 모든 warning들을 무시하고 싶은 경우
실행하고자 하는 파일 안에서 다음과 같은 함수를 정의해줍니다.

{% highlight python linenos %}
import warnings

def warn(*args, **kwargs):
  pass

# 저는 아래와 같이 사용합니다
# warn = lambda *args, **kwargs: None

warnings.warn = warn

# 혹은

import warnings
warnings.filterwarnings(action='ignore')
{% endhighlight %}[^1]

<br>
# 2. 특정 warning들만 무시하고 싶은 경우
{% highlight python linenos %}
import warnings
from sklearn.exceptions import DataConversionWarning

warnings.filterwarnings(action='ignore', category=DataConversionWarning)
{% endhighlight %}[^2]

---

[^1]: [https://stackoverflow.com/a/33616192/9002438](https://stackoverflow.com/a/33616192/9002438)
[^2]: [https://stackoverflow.com/a/47749756/9002438](https://stackoverflow.com/a/47749756/9002438)
