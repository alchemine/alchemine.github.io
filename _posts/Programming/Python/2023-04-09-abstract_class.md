---
title: Abstract Class
tags: Python
---

<!--more-->

Python은 추상 클래스를 구현하기 위해 `abc` 내장 library를 제공한다.

```python
from abc import ABCMeta, abstractmethod

class SuperClass(metaclass=ABCMeta):
    def __init__(self, a, b):
        self.a = a
        self.b = b
    
    @abstractmethod
    def method(self, d):
        raise NotImplementedError


class SubClass(SuperClass):
    def __init__(self, a, b, c):
        super().__init__(a, b)
        self.c = c
    
    def method(self, d):
        print(self.a, self.b, self.c, d)
        return "SubClass.method()"
```
