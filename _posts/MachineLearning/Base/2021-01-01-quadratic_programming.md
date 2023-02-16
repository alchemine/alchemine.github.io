---
title: Quadratic programming solver
tags: MachineLearning_Base
---

<!--more-->

Python에서 Quadratic programming 혹은 convex optimization을 위한 solver로 [OSQP](https://osqp.org/), [CVXPY](https://www.cvxpy.org/) 등이 있지만 저는 가장 robust하다고 하는 [CVXOPT](https://cvxopt.org/) package를 사용하고 있습니다.

<br>

![jpg](/deprecated/images/2021-01-01-quadratic_programming/001.jpg)


## Quadratic programming
![png](/deprecated/images/2021-01-01-quadratic_programming/002.png)


| Notation | Meaning | Shape |
|:--:|:--:|:--:|
| $n$ | number of elements of the solution vector | $()$ |
| $m$ | number of inequality constraints | $()$ |
| $p$ | number of equality constraints | $()$ |
| $x$ | solution vector | $(n, 1)$ |
| $P$ | quadratic coefficient matrix (positive semidefinite) | $(n, n)$ |
| $q$ | linear coefficient vector | $(n, 1)$ |
| $G$ | Inequality constraint coefficient matrix | $(m, n)$ |
| $h$ | Inequality constraint constant vector | $(m, 1)$ |
| $A$ | Equality constraint coefficient matrix | $(p, n)$ |
| $b$ | Equality constraint constant vector | $(p, 1)$ |


$$
\text{minimize }
\begin{aligned}
  \frac{1}{2}
  \begin{pmatrix}
    x_1 & \cdots & x_n \\
  \end{pmatrix}
  \begin{pmatrix}
    P_{11} & \cdots & P_{1n}\\
    \vdots & \ddots & \vdots\\
    P_{n1} & \cdots & P_{nn}\\
  \end{pmatrix}
  \begin{pmatrix}
      x_1 \\
      \vdots \\
      x_n \\
  \end{pmatrix} +
  \begin{pmatrix}
    q_1 & \cdots & q_n \\
  \end{pmatrix}
  \begin{pmatrix}
      x_1 \\
      \vdots \\
      x_n \\
  \end{pmatrix}
\end{aligned}
\\
\text{subject to }
\begin{pmatrix}
  G_{11} & \cdots & G_{1n}\\
  \vdots & \ddots & \vdots\\
  G_{m1} & \cdots & G_{mn}\\
\end{pmatrix}
\begin{pmatrix}
    x_1 \\
    \vdots \\
    x_n \\
\end{pmatrix} \preceq
\begin{pmatrix}
    h_1 \\
    \vdots \\
    h_m \\
\end{pmatrix}
\\ \quad \quad \quad \quad \
\begin{pmatrix}
  A_{11} & \cdots & A_{1n}\\
  \vdots & \ddots & \vdots\\
  A_{p1} & \cdots & A_{pn}\\
\end{pmatrix}
\begin{pmatrix}
    x_1 \\
    \vdots \\
    x_n \\
\end{pmatrix} =
\begin{pmatrix}
    b_1 \\
    \vdots \\
    b_p \\
\end{pmatrix}
$$
<br>


Quadratic program를 풀기 위해서 먼저 해야할 일은 문제를 [quadratic form](https://alchemine.github.io/2020/01/16/quadratic_form.html#gsc.tab=0)으로 변형시키는 것입니다.
구체적으론 위의 식의 $P, q, G, h, A, b$ 를 구하는 일이죠.

물론, 제약조건 여부에 따라 $G, h, A, b$ 를 사용하지 않고 $P, q$ 만 가지고 있어도 됩니다.
Data는 double type(`np.float64` or `np.double`)의 `cvxopt.matrix()` 형태로 입력해야 합니다.

간단한 linear regression 예제를 통해 사용방법을 알아봅시다!

$$
 min \ \frac{1}{2}|| S'w - y ||^2  \\
 s.t. \sum_t w_t = 1  \\
 \quad \ \ \ \forall_t w_t \geq 0
$$

위 식을 풀어보면 아래와 같이 표현할 수 있습니다.

$$
 min \ \frac{1}{2} w'(SS')w + (-Sy)'w  \\
 s.t. -Iw \leq \mathbf{0} \\
 \quad \ \ \ \mathbf{1}w = 1
$$

{% highlight python linenos %}
import numpy as np
from cvxopt import matrix, solvers


n = 15
T = 60

S = np.random.rand(n, T)
y = np.random.rand(T)

P = matrix(S @ S.T)
q = matrix(-S @ y)
G = matrix(-1 * np.identity(n))
h = matrix(np.zeros(n))
A = matrix(np.ones(n).reshape(1, n))
b = matrix(1.0)

solvers.options['show_progress'] = False  # verbose=False

sol = solvers.qp(P, q, G, h, A, b)
w = sol['x']
{% endhighlight %}

```
[ 2.71e-06]
[ 1.23e-01]
[ 7.77e-02]
[ 2.19e-02]
[ 7.99e-02]
[ 1.66e-01]
[ 8.54e-09]
[ 1.77e-08]
[ 1.62e-09]
[ 1.04e-01]
[ 5.16e-09]
[ 1.03e-01]
[ 9.16e-02]
[ 1.60e-09]
[ 2.33e-01]
```
