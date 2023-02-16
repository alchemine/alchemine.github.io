---
title: Custom dictionary
tags: Python
---

<!--more-->

오늘은 `python`에서 가장 자주 사용하는 자료구조 중 하나인 `dict`에 대한 글이다.  
종종 `dict`를 여러 번 중첩하여 사용하는 경우가 있다.  
이러한 경우, 내부에 있는 element에 접근하는데 코드가 길어지고 이해하기가 어려워지는 문제를 자주 느껴왔다.

이러한 문제를 해결하기 위해 직접 `dict` 자료구조를 customizing 하는 방법을 사용할 수 있지만, 귀찮아서 꾹꾹 참고 있다 결국 불편함이 도를 넘어 오늘 이후 계속 우려먹기 위해 칼을 뽑아 들었다.


{% highlight python linenos %}
import numpy as np
from collections import UserDict, Iterable


class ArrDict(UserDict):
    def __missing__(self, idx):
        rst = dict()
        for key, val in self.data.items():
            try:
                rst[key] = val if isinstance(val, str) else val[idx]
            except KeyError:
                rst[key] = val
        return rst


NUM_DATA    = 10
NUM_FEATURE = 3
data = ArrDict(
    features=ArrDict({f"feature{idx_feature}": idx_feature*np.arange(NUM_DATA) for idx_feature in range(NUM_FEATURE)}),
    targets=np.arange(NUM_DATA),
    param=dict(param0=0.1, param1='str', param2=True),
    desc=f"This is dataset with #data({NUM_DATA}), #feature({NUM_FEATURE})"
)
{% endhighlight %}


    data
    
```    
{'features': {'feature0': array([0, 0, 0, 0, 0, 0, 0, 0, 0, 0]),
              'feature1': array([0, 1, 2, 3, 4, 5, 6, 7, 8, 9]),
              'feature2': array([0, 2, 4, 6, 8, 10, 12, 14, 16, 18])},
 'targets': array([0, 1, 2, 3, 4, 5, 6, 7, 8, 9]),
 'param': {'param0': 0.1, 'param1': 'str', 'param2': True},
 'desc': 'This is dataset with #data(10), #feature(3)'}
```

    data[1]

```
{'features': {'feature0': 0,
              'feature1': 1,
              'feature2': 2},
 'targets': 1,
 'param': {'param0': 0.1, 'param1': 'str', 'param2': True},
 'desc': 'This is dataset with #data(10), #feature(3)'}
```


최대한 심플하게 짜려고 했는데 막상 짜보니까 생각보다 복잡해졌다.  
실용적으로 쓸 수 있을까?