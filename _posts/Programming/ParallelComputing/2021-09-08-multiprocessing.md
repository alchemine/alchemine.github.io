---
title: Multiprocessing with Queue
tags: ParallelComputing
---

<!--more-->

Process 병렬화를 할 때 process들을 queue로 관리하고 싶은 경우, `multiprocessing.Queue`를 사용하면 간단하다.(`queue.Queue`는 thread-safe하지 않아서 사용 X)

`dask` 기반으로 병렬처리를 구현하고 싶었는데 thread 병렬화는 제대로 작동하지만 process 병렬화는 process 간의 queue 공유가 잘 작동하지 않아서 결국 `multiprocessing` 모듈을 사용하기로했다.

다음은 예제 코드. 깔끔하게 뽑힌 것 같아서 기분이 좋다.

{% highlight python linenos %}
from multiprocessing import Process, Queue
from tqdm import tqdm
from time import sleep


class ProcessManager:
    def __init__(self, q_maxsize):
        self.q = Queue(q_maxsize)
    def __del__(self):
        self.q.close()
    def run(self, fn, args):
        ### 1. Generate all subprocesses
        procs = [Process(target=self._target_wrapper(fn), args=(arg,)) for arg in list(args)]

        ### 2. Start subprocesses
        for proc in procs:
            proc.daemon = True
            proc.start()

        ### 3. Join all subprocesses
        for proc in tqdm(procs):  # tqdm does not guarantee speeds
            proc.join()


    def _target_wrapper(self, fn):
        def wrap_fn(*args, **kwargs):
            self.q.put(None)
            rst = fn(*args, **kwargs)
            self.q.get()
            return rst
        return wrap_fn


def fn(arg):
    ### Execute with param
    for i in range(3):
        sleep(1)
    print(f"\n> task {arg}: finished")


if __name__ == '__main__':
    pm = ProcessManager(q_maxsize=2)
    pm.run(fn, [1, 2, 3, 4, 5])
{% endhighlight %}


```
  0%|                                                     | 0/5 [00:00<?, ?it/s]
> task 1: finished

> task 2: finished
 20%|█████████                                    | 1/5 [00:03<00:12,  3.00s/it]
> task 3: finished

> task 4: finished
 60%|███████████████████████████                  | 3/5 [00:06<00:03,  1.89s/it]
> task 5: finished
100%|█████████████████████████████████████████████| 5/5 [00:09<00:00,  1.80s/it]
```