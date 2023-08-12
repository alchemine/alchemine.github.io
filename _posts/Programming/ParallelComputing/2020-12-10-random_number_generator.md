---
title: Random number generator
tags: ParallelComputing
---

# Remarks
이 글은 `numba.cuda`를 기반으로 작성되었습니다.

<!--more-->

--- 

`numpy`에서 `seed`를 통해 난수를 생성하는 것처럼 `cuda`도 `seed`를 입력받아 먼저 periods(random states)를 생성하고 그로부터 직접 하나씩 난수를 뽑습니다.


{% highlight python linenos %}
from numba import cuda, int32
from numba.cuda.random import create_xoroshiro128p_states
from numba.cuda.random import xoroshiro128p_uniform_float32, xoroshiro128p_uniform_float64


# Parmaeters
N = 2**7
M = 2**23
SEED = 42

# Data
num_overflows = cuda.pinned_array(N, dtype=np.int32)


# 1. Generate random states
rng_states = create_xoroshiro128p_states(N, seed=SEED)


# 2. Define kernel function
@cuda.jit
def F(num_overflows, m, rng_states):
    tid = cuda.grid(1)
    num_overflows[tid] = 0
    
    for i in range(m):
        random = int32(xoroshiro128p_uniform_float32(rng_states, tid))
        # random = int32(xoroshiro128p_uniform_float64(rng_states, tid))
        if random == 1:
            num_overflows[tid] += 1


# 3. Execute kernel function
F[1, N](num_overflows, M, rng_states)
print(sum(num_overflows))
print(num_overflows)
{% endhighlight %}

```
31
[1 1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 0 1 0 0 0 1 1 1 0 0 0 0 0 0 0 0 1 0
 0 0 1 0 0 1 0 0 0 1 0 0 0 1 1 0 0 0 0 1 0 0 2 1 0 1 0 0 0 1 0 0 0 0 0 0 0
 0 1 0 0 0 0 1 1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 0 0 1 0 1 0 0 1 0 0
 1 0 0 0 0 1 0 0 0 0 1 2 0 0 0 0 0]
```

`create_xoroshiro128p_states()`는 각 thread 당 $2^{64}$ steps까지는 독립적으로 sampling되는 것을 보장해주는 random states를 반환하는 함수입니다. 

난수를 생성할 때 `xoroshiro128p_uniform_float32()` 를 사용하면 `[0.0, 1.0)` 범위의 uniform 분포에서 `float32` 정밀도의 값을 반환하는데 `int32` 등의 다른 type으로 변환하게 되는 경우 1이 반환되는 경우가 있습니다. 위의 예시에선, $2^{30}$ 번 중에 31번 나타났죠. `float32` 대신 `float64` 로 정밀도를 높여 반환시키면 어느정도 해결됩니다. (`xoroshiro128p_uniform_float64()`)

```
 0
[0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0]
```