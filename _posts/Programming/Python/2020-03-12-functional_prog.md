---
title: filter, map, reduce
tags: Python
---

<!--more-->

입력값에 대하여 함수를 적용하는 작업을 효율적으로 할 수 있도록 Python은 `filter`, `map`, `reduce`라는 함수를 제공합니다.  


```python
from sys import getsizeof as sizeof


f = lambda x: x % 2 == 0
t = tuple(map(f, range(10)))
l = list(map(f, range(10)))

print(l)
print(sizeof(t), sizeof(l))  # list is more flexible but has larger size
```

    [True, False, True, False, True, False, True, False, True, False]
    136 168



```python
l = list(filter(f, range(10)))
print(l)
```

    [0, 2, 4, 6, 8]



```python
from functools import reduce

f = lambda cum_val, val: cum_val + val
t = reduce(f, range(10))
print(t)
```

    45

