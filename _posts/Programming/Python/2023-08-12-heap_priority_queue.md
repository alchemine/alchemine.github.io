---
title: Heap & Priority Queue
tags: Python
---

<!--more-->

Sequence 안에서 min 혹은 max 값을 연속적으로 추출해내는 수행을 할 땐, `O(log n)` 복잡도를 가지는 Heap 혹은 Priority Queue를 사용하는 것이 바람직하다.


# 1. Heap
2가지만 신경쓰면 된다.

1. `item` 구성: `(priority, element)`
2. Min-heap


```python
from heapq import heapify, heappush, heappop

arr = [(1, 'z'), (2, 'y'), (3, 'x')]  # list(priority, element)
heapify(arr)
heappush(arr, (4, 'w'))
heappush(arr, (5, 'v'))

while arr:
    peek = arr[0]  # [0] = root node = min element
    elem = heappop(arr)
    print(peek, elem)
```

```
(1, 'z') (1, 'z')
(2, 'y') (2, 'y')
(3, 'x') (3, 'x')
(4, 'w') (4, 'w')
(5, 'v') (5, 'v')
```


# 2. Priority Queue
여긴 3가지

1. 내부적으론 heap으로 구현되어 있지만, `heapq`와는 달리 기존 sequence로 초기화가 불가능
2. `item` 구성: `(priority, element)`
3. Min-heap

```python
from queue import PriorityQueue

Q = PriorityQueue()
Q.put((1, 'z'))  # (priority, element)
Q.put((2, 'y'))
Q.put((3, 'x'))
Q.put((4, 'w'))
Q.put((5, 'v'))

while not Q.empty():
    peek = Q.queue[0]  # [0] = root node = min element
    elem = Q.get()
    print(peek, elem)
```

```
(1, 'z') (1, 'z')
(2, 'y') (2, 'y')
(3, 'x') (3, 'x')
(4, 'w') (4, 'w')
(5, 'v') (5, 'v')
```
