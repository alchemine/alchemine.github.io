---
title: Maximize GPU utilization
tags: ParallelComputing
---

<!--more-->

어른들의 사정으로 GPU 사용량을 최대로 유지해줄 필요가 있을 수 있다.  
이때 사용할 수 있는 간단한 코드를 짜보았다.  

`numba`와 `dask` package가 필요한데 둘 다 `pip`로 간단히 설치가능하다.  


{% highlight python linenos %}
from time import sleep, time
from numba import cuda
from dask import delayed, compute


### Constants
BPG   = 2 ** 0
TPB   = 2 ** 10
N_GPU = len(cuda.gpus)


### GPU kernel function
@cuda.jit
def compute_infinite_loop(a):
    tid = cuda.grid(1)
    while True:
        a[tid] *= 1


### Utility function
@delayed
def get_task(idx_gpu):
    with cuda.gpus[idx_gpu]:
        arr = cuda.device_array(shape=BPG*TPB, dtype=float)
        compute_infinite_loop[BPG, TPB](arr)
def timer():
    start_time = time()
    while True:
        print(f"\rElapsed time: {(time() - start_time) / 60:.1f}m", end='')
        sleep(1)


if __name__ == "__main__":
    try:
        compute(*[get_task(idx_gpu) for idx_gpu in range(N_GPU)])
        timer()
    except KeyboardInterrupt:  # Ctrl + C
        print('\n' + "[Process is killed]" + '\n')
{% endhighlight %}
