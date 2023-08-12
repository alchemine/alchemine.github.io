---
title: Numba parallel example
tags: ParallelComputing
---

<!--more-->

# Problem
## - Input
- 크기가 10인 array `a`
- 모든 원소가 0으로 초기화된 $[2^{24}, 200]$ 형태의 matrix `b`

## - Output
- Matrix `b`의 앞부분 10개의 열이 `a`의 값으로 갱신된 matrix


# Experiments
1. **Numpy (7.87s)**  
- 간단한 broadcasting을 이용

2. **Naive Numba (8.03s)**  
- Numpy 구현과 동일한 함수를 사용

3. **Numba Parallel 1 (1.3s)**  
- Numpy 구현과 동일한 함수를 사용
- `parallel=True` 추가

4. **Numba Parallel 2 (1.28s)**
- 메모리 접근 횟수를 최소화시키기 위해 `b`를 traspose 시켜 입력으로 받음
- Broadcasting을 사용하는 대신 loop를 추가

5. **Numba Parallel 3 (1.32s)**  
- 메모리 접근 횟수를 최소화시키기 위해 `b`를 traspose 시켜 입력으로 받음
- Broadcasting을 사용하는 대신 loop를 추가
- Matrix에 매번 접근하는대신 `tmp` 변수에 사용할 배열을 저장하여 사용

6. **Numba Parallel 4 (1.22s)**
- Broadcasting을 사용하는 대신 loop를 추가
- Matrix에 매번 접근하는대신 `tmp` 변수에 사용할 배열을 저장하여 사용

7. **Numba Parallel 5 (1.07s)**
- Broadcasting을 사용하는 대신 loop를 추가


# Analysis
1. Input들을 GPU로 옮기는, 받아오는데 걸리는 시간이 6초가 넘어 CPU 병렬화로 해결하였다.
2. **1, 2 비교**  
`@numba.njit` 쓴다고 무조건 빨라지는 건 아니다.
3. **2, 3 비교**  
**`@numba.njit`의 여러가지 옵션들(`parallel`, `vectorize`, `guvectorize` 등)을 적재적소에 사용**하는 것이 성능향상의 핵심이다.
4. **3, 4 비교**  
`Numba(CPU)`는 broadcasting을 지원하고 좋아한다고 하지만 성능의 차이가 존재한다.
5. **4, 5 비교** 및 **6, 7 비교**  
메모리 접근 속도의 차이가 현저한 GPU 프로그래밍과는 달리 모든 변수들이 접근속도가 크게 차이나지 않기 때문에 오히려 새로운 변수를 사용하는 것이 좋지 못한 결과를 보였다.
6. **4, 7 비교**  
`b`를 그대로 입력하고 broadcasting을 사용하지 않았다.

## - 결론
몇 가지 실험을 돌려본 결과 `numba`를 이용하여 `numpy`를 통해 구현했을 때보다 약 8배 정도 빠른 성능향상을 보여주었다. 이 문제에서 성능향상의 핵심은 2가지였다.  

1. `numba.njit` 옵션 중 `parallel=True` 를 사용
2. Broadcasting 대신 풀어 loop를 추가

가능하다면 `guvectorize` 옵션도 사용하고 싶었지만 다음 기회에 해보기로하였다.


# Code
## 0. Import libraries

```python
import numpy as np
import numba
from numba import prange
```

## 1. Numpy (7.87s)


```python
%%timeit

def fn(a, b):
    for i in range(len(a)):
        b[:, i] = a[i]

N = 2**24
a = np.arange(10, dtype=np.int32)
b = np.zeros([N, 200], dtype=np.int32)
fn(a, b)
```

    7.87 s ± 55.2 ms per loop (mean ± std. dev. of 7 runs, 1 loop each)


## 2. Naive Numba (8.03s)


```python
%%timeit

@numba.njit
def fn(a, b):
    for i in range(len(a)):
        b[:, i] = a[i]

N = 2**24
a = np.arange(10, dtype=np.int32)
b = np.zeros([N, 200], dtype=np.int32)
fn(a, b)
```

    8.03 s ± 82.9 ms per loop (mean ± std. dev. of 7 runs, 1 loop each)


## 3. Numba Parallel 1 (1.3s)


```python
%%timeit

@numba.njit(parallel=True)
def fn(a, b):
    for i in range(len(a)):
        b[:, i] = a[i]

N = 2**24
a = np.arange(10, dtype=np.int32)
b = np.zeros([N, 200], dtype=np.int32)
fn(a, b)
```

    1.3 s ± 19.2 ms per loop (mean ± std. dev. of 7 runs, 1 loop each)



## 4. Numba Parallel 2 (1.28s)


```python
%%timeit

@numba.njit(parallel=True)
def fn(a, b_T):
    for i in range(len(a)):
        for j in prange(len(b_T[i])):
            b_T[i, j] = a[i]
            
N = 2**24
a = np.arange(10, dtype=np.int32)
b = np.zeros([N, 200], dtype=np.int32)
b_T = b.T
fn(a, b_T)
b = b_T.T
```

    1.28 s ± 19.1 ms per loop (mean ± std. dev. of 7 runs, 1 loop each)


## 5. Numba Parallel 3 (1.32s)


```python
%%timeit

@numba.njit(parallel=True)
def fn(a, b_T):
    for i in range(len(a)):
        tmp = b_T[i]
        val = a[i]
        for j in prange(len(tmp)):
            tmp[j] = val
            
N = 2**24
a = np.arange(10, dtype=np.int32)
b = np.zeros([N, 200], dtype=np.int32)
b_T = b.T
fn(a, b_T)
b = b_T.T
```

    1.32 s ± 46.2 ms per loop (mean ± std. dev. of 7 runs, 1 loop each)



## 6. Numba Parallel 4 (1.22s)


```python
%%timeit

@numba.njit(parallel=True)
def fn(a, b):
    for i in prange(len(b)):
        tmp = b[i]
        for j in range(len(a)):
            tmp[j] = a[j]
            
N = 2**24
a = np.arange(10, dtype=np.int32)
b = np.zeros([N, 200], dtype=np.int32)
fn(a, b)
```

    1.22 s ± 17.4 ms per loop (mean ± std. dev. of 7 runs, 1 loop each)


## 7. Numba Parallel 5 (1.07s)


```python
%%timeit

@numba.njit(parallel=True)
def fn(a, b):
    for i in prange(len(b)):
        for j in range(len(a)):
            b[i, j] = a[j]
            
N = 2**24
a = np.arange(10, dtype=np.int32)
b = np.zeros([N, 200], dtype=np.int32)
fn(a, b)
```

    1.07 s ± 15.4 ms per loop (mean ± std. dev. of 7 runs, 1 loop each)
