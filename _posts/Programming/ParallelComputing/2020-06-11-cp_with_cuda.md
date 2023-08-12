---
title: Cupy ndarray as CUDA input
tags: ParallelComputing
---

<!--more-->

`numba.cuda`의 kernel(device) function의 input으로 `numpy` ndarray 객체를 사용할 수 있지만, 불필요한 transfer time을 줄이기 위해 `cuda.to_device()` 혹은 `cuda.device_array()` 등으로 생성된 `DeviceNDArray`를 주로 사용한다. 이는 `numpy` 객체와는 달리 변수가 GPU 상으로 올라가기 때문인데 `cupy` ndarray 객체 또한 GPU(CUDA device) memory 위에서 생성되기 때문에 RAM ↔ VRAM 간의 불필요한 전송을 줄일 수 있다.

이를 확인하기 위해 $2^26$개의 원소를 가진 array를 각각 `numpy.ndarray`, `numba.cuda.cudadrv.devicearray.DeviceNDArray`, `cupy.core.core.ndarray`로 변환하여 몇 가지 연산을 하는 kernel function의 input으로 사용하여 소요되는 시간을 체크하는 실험을 해보았다.


예상대로 `numpy` 객체는 100배 이상이 넘는 시간을 보여주었다. Device로 data를 올리는데 걸리는 시간이 오히려 병목이 되지 않는 이상 `numpy` 객체를 input으로 사용하는 것은 지양하는 것이 바람직하다.

`cuda` 객체는 `cupy` 객체보다 약 10% 빠른 속도를 보여주었다. `cupy` 객체는 host로 data를 전송하지 않아도 그 값을 확인해볼 수 있고 다양한 `numpy`의 함수들을 사용할 수 있는데 CUDA programming에서도 속도면에서 크게 밀리지 않았다는 것이 아주 훌륭하다. 자주 애용해야겠다.


```python
import numpy as np
import cupy as cp
from numba import cuda
import math

@cuda.jit
def fn(a):
    tid = cuda.grid(1)
    a[tid] = a[tid] * a[tid] / a[tid] + math.log(a[tid]) - math.log(a[tid])
    cuda.syncthreads()


N = 2**26
NUM_BLOCK = 2**17
NUM_THREAD = 2**9

a = np.arange(N, dtype=np.float32)  # numpy.ndarray
dev_a = cuda.to_device(a)           # numba.cuda.cudadrv.devicearray.DeviceNDArray
cp_a  = cp.asarray(a)               # cupy.core.core.ndarray
```

```python
%%timeit
fn[NUM_BLOCK, NUM_THREAD](a)
cuda.synchronize()
```

    135 ms ± 201 µs per loop (mean ± std. dev. of 7 runs, 10 loops each)
    

```python
%%timeit
fn[NUM_BLOCK, NUM_THREAD](dev_a)
cuda.synchronize()
```

    1.11 ms ± 1.71 µs per loop (mean ± std. dev. of 7 runs, 1000 loops each)
    
    
```python
%%timeit
fn[NUM_BLOCK, NUM_THREAD](cp_a)
cuda.synchronize()
```

    1.28 ms ± 2.55 µs per loop (mean ± std. dev. of 7 runs, 1000 loops each)