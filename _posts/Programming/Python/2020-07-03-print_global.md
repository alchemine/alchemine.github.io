---
title: Print global variables
tags: Python
---

<!--more-->

전역변수는 `globals()` namespace 안에 존재하고 있는데 이곳에는 변수들뿐만 아니라 `module`, `function`, `class` 등 우리가 알고싶지 않은 잡다한 값들도 많이 포함되어 있습니다.  

따라서 전역변수만을 출력하고 싶은 경우엔 이러한 것들을 필터링할 필요가 있습니다.


```Python
def print_global_vars():
    tmp = globals()
    stopword = ['In', 'Out', 'exit', 'quit', 'get_ipython']
    for key, val in tmp.items():
        if not (key.startswith('_') or key in stopword or type(val) == types.ModuleType or type(val) == types.FunctionType):
            print(key, val)
```

```py
A = 10
B = 20
C = {'a': 10, 'b': 20}
D = [10, 20]
```

```py
print_global_vars()
```

```
A 10
B 20
C {'a': 10, 'b': 20}
D [10, 20]
```
