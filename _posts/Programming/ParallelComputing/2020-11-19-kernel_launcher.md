---
title: Kernel launcher
tags: ParallelComputing
---

# Remarks
이 글은 `numba.cuda`를 기반으로 작성되었습니다.

<!--more-->

---

`numba.cuda`의 kernel function은 default argument를 지원하지 않습니다.  
그래서 여러 개의 고정된 parameter를 가진 함수를 여러 번 실행시킬 때 관리하기가 쉽지 않습니다.  
특히 parameter가 특정 조건에 따라 변하거나 여러 개의 GPU를 사용해야 하는 경우라면 더더욱 그렇죠.  

이런 경우 kernel function에 들어가는 parameter를 설정하고 kernel function을 실행시키는 class를 생성하여 parameter를 관리하면 편리합니다. 이러한 역할을 담당하는 class를 **KernelLauncher**라고 명명했습니다.  


{% highlight python linenos %}
class KernelLauncher:
    def __init__(self, *params):
        self.fn, self.param, self.BPG, self.TPB = params

    def set_param(self, param):
        self.param = param

    def run(self, idx_gpu=-1):
        if idx_gpu >= 0:
            idx_param = []
            for elem in self.param:
                try:
                    idx_param.append(elem[idx_gpu])
                except:
                    idx_param.append(elem)  # elem: scalar
            self.fn[self.BPG, self.TPB](*idx_param)
        else:
            self.fn[self.BPG, self.TPB](*self.param)
{% endhighlight %}

{% highlight python linenos %}
class A:
  def __init__(self):
    self.a   = None
    self.b   = None
    self.c   = None
    self.BPG = None
    self.TPB = None
  
  def get_kernel(self, flag):
    if flag is None:
      @cuda.jit
      def fn(a, b, c):
        pass
      param = (self.a, self.b, self.c)
      BPG, TPB = self.BPG, self.TPB
    return fn, param, BPG, TPB

  def initialize_kernel_launcher(self, flag=None):
    self.kernel_launcher = KernelLauncher(*self.get_kernel(flag))

  def run_kernel(self, idx_gpu):
    self.kernel_launcher.run(idx_gpu)
{% endhighlight %}

Kernel 함수와 parameter, BPG(Block Per Grid), TPB(Thread Per Block)를 반환하는 함수를 호출하여 `KernelLauncher` instance를 생성하고 상황에 맞게 `run()`을 실행시키면 됩니다.
