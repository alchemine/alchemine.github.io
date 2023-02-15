---
title: Handling precision in Python
tags: Python
---

<!--more-->


Python의 `int` type은 4Bytes로 $-2^{31} \sim 2^{31} - 1$ 의 범위의 정수형 자료를 나타낸다.  
조금 더 넓은 범위의 수를 나타내는 데에는 `long` type을 사용하는데 타 언어와 달리 Python의 `long` type은 표현할 수 있는 범위가 무한대이다. 물론 그만큼 더 많은 개수의 bit가 필요하다.

Python의 `float` type은 double precision이다.  
내장함수 `Decimal()`을 사용하면 임의의 precision으로 분수의 형태로 숫자를 표현할 수 있다.  

[https://stackoverflow.com/questions/6663272/double-precision-floating-values-in-python](https://stackoverflow.com/questions/6663272/double-precision-floating-values-in-python) 참조


```python
import decimal
from decimal import Decimal

decimal.getcontext()
```

```
Context(prec=28, rounding=ROUND_HALF_EVEN, Emin=-999999, Emax=999999, capitals=1, clamp=0, flags=[], traps=[InvalidOperation, DivisionByZero, Overflow])
```


```python
a = Decimal(1) / Decimal(9);  print(f"prec({decimal.getcontext().prec}): {a}")

decimal.getcontext().prec = 10
b = Decimal(1) / Decimal(9);  print(f"prec({decimal.getcontext().prec}): {b}")

decimal.getcontext().prec = 40
c = Decimal(1) / Decimal(9);  print(f"prec({decimal.getcontext().prec}): {c}")

d = a + b + c;  print("Sum     :", d)
```

```
prec(28): 0.1111111111111111111111111111
prec(10): 0.1111111111
prec(40): 0.1111111111111111111111111111111111111111
Sum     : 0.3333333333222222222222222222111111111111
```