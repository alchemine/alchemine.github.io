---
title: Simple example with Numba
tags: ParallelComputing
aside:
  toc: true
---


<!--more-->
#### Problem
$2 \times 2^{20} \times 2^{10} \approx 2 \times 10^9$개의 원소가 모두 0인 배열을 입력받아 각 원소의 값에 1을 더하는 예제입니다.

#### Enviornment
**CPU**: Intel(R) Core(TM) i5-7500 CPU @ 3.40GHz (4 Cores)
**GPU**: GeForce GTX 1080 Ti (33MHz) x 2


#### Experiment methods
실험한 방법은 총 4가지입니다.

1. `Numba.njit` (1 CPU)
2. `Numba.cuda.jit` / Implicit transfer (1 GPU)
3. `Numba.cuda.jit` / Implicit transfer (2 GPU)
4. `Numba.cuda.jit` / Explicit transfer (2 GPU)

#### Result
| Method | First time | Second time |
|:--:|:--:|:--:|
| Numba.njit (1 CPU) | 4.62s | 629ms |
| Numba.cuda.jit Implicit transfer (1 GPU) | 6.22s | 2.86s |
| **Numba.cuda.jit Implicit transfer (2 GPU)** | 4.87s | 1.72s |
| Numba.cuda.jit Explicit transfer (2 GPU) | 3.6s | 3.15s |

각 원소에 대하여 연산이 한 번 밖에 없는 간단한 문제이기 때문에 오히려 GPU를 사용할 때 병목현상이 일어나 CPU를 사용할 때 더 좋은 결과가 나온 것으로 보입니다.  
코드를 단 한 번만 사용할 경우, 4번 방법이 가장 좋아보입니다. 그러나 다른 방법들에 비해 코드가 조금 조악하고 동일한 parameter에 대하여 두 번째로 실행했을 때 원하는 결과가 나오지 않아 추가적인 손질이 필요할 것으로 보입니다.  
따라서 일반적으론 무난하게 3번 방법을 추천하고 사용하는 것으로 결론을 내렸습니다.


#### Code
1. `Numba.njit` (1 CPU)
```python
import numpy as np
import numba


blocks_per_grid = 2**20
threads_per_block = 2**10
arr = np.zeros(2 * blocks_per_grid * threads_per_block, dtype=np.int32)

@numba.njit
def convert_to_one(arr):
    for i in range(len(arr)):
        arr[i] += 1

%time convert_to_one(arr)
%time convert_to_one(arr)
print(np.all(arr), arr)
```

    CPU times: user 1.57 s, sys: 3.04 s, total: 4.6 s
    Wall time: 4.58 s
    CPU times: user 634 ms, sys: 845 µs, total: 635 ms
    Wall time: 633 ms
    True [2 2 2 ... 2 2 2]


2. `Numba.cuda.jit` / Implicit transfer (1 GPU)
```python
import numpy as np
from dask import delayed, compute
from numba import cuda


blocks_per_grid = 2**20
threads_per_block = 2**10

arr = np.zeros(2 * blocks_per_grid * threads_per_block, dtype=np.int32)
arr_01 = np.array_split(arr, 2)

@cuda.jit
def convert_to_one(one_arr):
    tid = cuda.grid(1)
    if tid < one_arr.size:
        one_arr[tid] += 1

@delayed
def select_gpu(one_arr, num_gpu):
    # cuda.select_device(num_gpu)
    convert_to_one[blocks_per_grid, threads_per_block](one_arr)

list_fn = [select_gpu(one_arr, num_gpu) for num_gpu, one_arr in enumerate(arr_01)]

print("Start")
%time compute(list_fn, scheduler='threads')  # First
%time compute(list_fn, scheduler='threads')  # Main
print(np.all(arr), arr)
```

    Start
    CPU times: user 3.02 s, sys: 3.25 s, total: 6.27 s
    Wall time: 6.23 s
    CPU times: user 2.77 s, sys: 30.8 ms, total: 2.8 s
    Wall time: 2.89 s
    True [2 2 2 ... 2 2 2]


3. `Numba.cuda.jit` / Implicit transfer (2 GPU)
```python
import numpy as np
from dask import delayed, compute
from numba import cuda


blocks_per_grid = 2**20
threads_per_block = 2**10

arr = np.zeros(2 * blocks_per_grid * threads_per_block, dtype=np.int32)
arr_01 = np.array_split(arr, 2)

@cuda.jit
def convert_to_one(one_arr):
    tid = cuda.grid(1)
    if tid < one_arr.size:
        one_arr[tid] += 1

@delayed
def select_gpu(one_arr, num_gpu):
    cuda.select_device(num_gpu)
    convert_to_one[blocks_per_grid, threads_per_block](one_arr)

list_fn = [select_gpu(one_arr, num_gpu) for num_gpu, one_arr in enumerate(arr_01)]

print("Start")
%time compute(list_fn, scheduler='threads')  # First
%time compute(list_fn, scheduler='threads')  # Main
print(np.all(arr), arr)
```

    Start
    CPU times: user 3.42 s, sys: 6.02 s, total: 9.44 s
    Wall time: 4.88 s
    CPU times: user 3.42 s, sys: 28 ms, total: 3.45 s
    Wall time: 1.75 s
    True [2 2 2 ... 2 2 2]


4. `Numba.cuda.jit` / Explicit transfer (2 GPU)
```python
import numpy as np
from dask import delayed, compute
from numba import cuda


blocks_per_grid = 2**20
threads_per_block = 2**10

arr = np.zeros(2 * blocks_per_grid * threads_per_block, dtype=np.int32)
arr_01 = np.array_split(arr, 2)

@cuda.jit
def convert_to_one(one_arr):
    tid = cuda.grid(1)
    if tid < one_arr.size:
        one_arr[tid] += 1

@delayed
def select_gpu(one_arr, num_gpu):
    cuda.select_device(num_gpu)
    one_arr = cuda.to_device(one_arr)
    convert_to_one[blocks_per_grid, threads_per_block](one_arr)
    return one_arr.copy_to_host()

list_fn = [select_gpu(one_arr, num_gpu) for num_gpu, one_arr in enumerate(arr_01)]
result_fn = delayed(np.concatenate)(list_fn)

print("Start")
%time result_arr = compute(result_fn)  # First
%time result_arr = compute(result_fn)  # Main
print(np.all(result_arr[0]), result_arr[0])
```
    
    Start
    CPU times: user 3.23 s, sys: 2.29 s, total: 5.52 s
    Wall time: 3.6 s
    CPU times: user 3.69 s, sys: 1.15 s, total: 4.85 s
    Wall time: 3.11 s
    True [1 1 1 ... 1 1 1]