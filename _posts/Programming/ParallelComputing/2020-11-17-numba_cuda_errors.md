---
title: Numba CUDA errors
tags: ParallelComputing
---

<!--more-->

`numba.cuda`를 사용하다보면 당연하게 사용하였던 코드가 문제가 되는 경우가 자주 발생합니다.  
매번 어떻게든 꾸역꾸역 넘어가긴 했지만 이제부턴 발생한 상황과 해결방법 등을 기록해두고자 합니다.  


## 1. `len()` → 상수
### 1) Code
```
### Error code

a = cuda.to_device(np.array([range(20) for _ in range(16)]))
b = cuda.device_array([32, 20])

@cuda.jit
def COPY(a, b):
    tid = cuda.grid(1)
    bid = cuda.blockIdx.x
    
    for i in range(len(a[bid])):  # Error with len(a[bid])
        b[tid][i] = a[bid][i]

COPY[16, 2](a, b)
b.copy_to_host()
```
```
CudaAPIError: [700] Call to cuMemcpyDtoH results in UNKNOWN_CUDA_ERROR
```

```
### Resolution code

a = cuda.to_device(np.array([range(20) for _ in range(16)]))
b = cuda.device_array([32, 20])

N = a.shape[1]

@cuda.jit
def COPY(a, b):
    tid = cuda.grid(1)
    bid = cuda.blockIdx.x
    
    for i in range(N):  # Error with len(a[bid])
        b[tid][i] = a[bid][i]

COPY[16, 2](a, b)
b.copy_to_host()
```

### 2) 원인
`len()` 혹은 indexing 시 register를 많이 소모하여 메모리 문제가 발생한 것 같다.



## 2. `math.sqrt(T - 1)` → `math.sqrt(cuda.float32(T) - 1)`
### 1) Code
```
### Error code
T = G.T  # int

@cuda.jit(device=True)
def GET_MEASURE(..):
  rst = (exp / risk) / math.sqrt(T - 1)
```

```
LoweringError: Failed in nopython mode pipeline (step: nopython mode backend)
No definition for lowering <built-in function sqrt>(int64,) -> float64
```

```
### Resolution code
T = G.T  # int

@cuda.jit(device=True)
def GET_MEASURE(..):
  rst = (exp / risk) / math.sqrt(float32(T) - 1)
```



### 2) 원인
Type 변환이 smooth하게 안 되는 경우가 간혹 있는 것 같다.
