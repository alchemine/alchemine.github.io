---
title: How to catch logger.warning()
tags: Python
---

<!--more-->

일반적으로 `Exception`을 상속받는 class들을 `try`, `except`문을 통해 처리해준다. \
보통 `warning`에 대한 처리는 `warnings.filterwarnings('error')`를 사용하지만
특정 `logger`에 대하여 `logger.warning()`을 호출하는 경우도 catch하고 싶은 경우,
함수를 변경하면 이들 역시 `try`, `except`문으로 잡아낼 수 있다. \
물론, 직접 함수를 변경하는 방식은 얼마든지 다른 곳에서도 응용이 가능하다.


{% highlight python linenos %}
def warning(msg, *args, **kwargs):
  raise Warning(msg % args)
logging.getLogger('distributed.client').warning = warning

try:
  ...
except Warning as e:
  print("[Warning]:", e)
{% endhighlight %}
