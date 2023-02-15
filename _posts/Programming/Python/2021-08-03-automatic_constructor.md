---
title: Automatic instance variable initialization
tags: Python
---

# Remarks
이 글은 [Automatically initialize instance variables?](https://stackoverflow.com/q/1389180) 질문과 답변에 기반하여 작성되었습니다.

<!--more-->

---

코드를 짜다보면 여러 개의 class를 만들게 된다. 이에 항상 따라오는 작업은 constructor에서 instance variables를 초기화해주는 작업이다. 이 작업은 처음 프로그래밍 언어를 배울 때부터 정말 귀찮은 작업이었다.

이를 간편하게 할 수 있는 별도의 언어적 차원의 지원이 없는 python에서 10년도 더 전에 이와 관련된 질문이 올라왔었다. 답변이 여러 개 있었는데 그 중에서 두 가지 방법들을 살펴보고자 한다.


### 1. Decorator로 처리하기
{% highlight python linenos %}
from functools import wraps
import inspect

def auto_initializer(func):
    """
    Automatically assigns the parameters.
    """

    @wraps(func)
    def wrapper(self, *args, **kwargs):
        for name, arg in list(zip(names[1:], args)) + list(kwargs.items()):
            setattr(self, name, arg)
        for name, default in zip(reversed(names), reversed(defaults)):
            if not hasattr(self, name):
                setattr(self, name, default)
        func(self, *args, **kwargs)
    return wrapper


class A:
    @auto_initializer
    def __init__(self, a, b, c, d):
        pass
{% endhighlight %}

Utility functions이 있는 `env.py` 같은 곳에 적당히 넣고 사용하면 좋을 것 같다.


### 2. `dataclass` 사용
{% highlight python linenos %}
from dataclasses import dataclass, field

@dataclass
class A:
    a: int
    b: ...
    c: dict
    d: list[int] = field(default_factory=list)

### Equal to

class A:
  def __init__(self, a: int, b, c: dict, d: list[int]=list()):
    self.a = a
    self.b = b
    self.c = c
    self.d = d
{% endhighlight %}


{% highlight python linenos %}
@dataclass
class C:
    a: float
    b: float
    c: float = field(init=False)

    def __post_init__(self):
        self.c = self.a + self.b
{% endhighlight %}


{% highlight python linenos %}
@dataclass
class Rectangle:
    height: float
    width: float

@dataclass
class Square(Rectangle):
    side: float

    def __post_init__(self):
        super().__init__(self.side, self.side)
{% endhighlight %}

{% highlight python linenos %}
@dataclass
class Base:
    x: Any = 15.0
    y: int = 0

@dataclass
class C(Base):
    z: int = 10
    x: int = 15
{% endhighlight %}

Python 3.7 에 추가된 모듈인 [`dataclasses`](https://docs.python.org/ko/3/library/dataclasses.html)는 `__init__()`이나 `__repr__()`과 같은 special method를 사용자 정의 class에 자동으로 추가하는 decorator와 function을 제공한다고 한다.  
Instance variable에 대하여 type signature이 반드시 필요하긴하지만 type 검사를 하지 않기 때문에 syntax error가 뜨지만 않으면 어떤 값이 들어가도 상관없다. ([typeless-dataclasses](https://pypi.org/project/typeless-dataclasses/)는 이러한 점을 지적하여 type에 대한 지정이 필요없는 dataclass를 지원한다. 그러나 오히려 덜 직관적이여서 보기에 영 좋지 않다.) [Dataclasses without type annotations](https://death.andgravity.com/dataclasses)에서는 이곳을 해당 variable에 대한 설명으로 채우는 것을 제안하기도 하였다. 역시 이런 유연한 점이 python의 큰 장점이라 생각된다.

{% highlight python linenos %}
@dataclass
class Data:
    one: "the first thing"
    two: "the second thing; an integer" = 2
{% endhighlight %}
