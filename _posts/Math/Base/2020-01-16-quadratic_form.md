---
title: Quadratic form
tags: Math_Base
---

# Remarks
이 글은 <br>
[https://en.wikipedia.org/wiki/Quadratic_form#Introduction](https://en.wikipedia.org/wiki/Quadratic_form#Introduction) <br>
[http://www.rmi.ge/~kade/LecturesT.Kadeishvili/MathEconomics/Term3/Week3QuadraticLEC.pdf](http://www.rmi.ge/~kade/LecturesT.Kadeishvili/MathEconomics/Term3/Week3QuadraticLEC.pdf) <br>
[https://en.wikipedia.org/wiki/Covariance_matrix](https://en.wikipedia.org/wiki/Covariance_matrix) <br>
[http://elearning.kocw.net/contents4/document/lec/2013/Chungbuk/LeeGeonmyeong1/14.pdf](http://elearning.kocw.net/contents4/document/lec/2013/Chungbuk/LeeGeonmyeong1/14.pdf) <br>
등을 참고하여 작성되었습니다.

<!--more-->

---

## 1. Introduction
**Quadratic form**은 homogeneous quadratic polynomial을 의미한다.(모든 항의 차수가 동일) <br>

- 다음과 같이 변수의 개수에 따라 이름이 붙여지기도 한다. <br>
**Unary** <br>
$q(x) = ax^2$ <br>
**Binary** <br>
$q(x, y) = ax^2 + bxy + cy^2$ <br>
**Ternary** <br>
$q(x, y, z) = ax^2 + bxy + cy^2 + dyz + ez^2 + fzx$ <br>

- 다음과 같은 notation을 사용하기도 한다.(diagonal form) <br>
$q(x) = \langle a_1, \cdots, a_n \rangle = a_1x_1^2 + \cdots + a_nx_n^2$

## 2. Matrix representation of quadratic form
임의의 $n \times n$ real *symmetric* matrix $A$는 $n$개의 변수를 가진 quadratic form $q_A$를 아래의 식으로 결정할 수 있다. <br>
$$
\begin{equation}
\begin{aligned}
  q_A(x_1, \cdots, x_n) &= \sum_i \sum_j a_{ij} x_i x_j \\
  &= \mathbf{x}^T A \mathbf{x} \\
  &=
  \begin{pmatrix}
  x_1 & \cdots & x_n \\
  \end{pmatrix}
  \begin{pmatrix}
  a_{11} & \cdots & a_{1n} \\
  \vdots & \ddots & \vdots \\
  a_{n1} & \cdots & a_{nn} \\
  \end{pmatrix}
  \begin{pmatrix}
  x_1 \\
  \vdots \\
  x_n \\
  \end{pmatrix}
\end{aligned}
\end{equation}
$$

역으로 $n$개의 변수에 대한 quadratic form이 주어진 경우, 해당 coefficient들을 $n \times n$ *symmetric* matrix의 형태로 만드는 것도 가능하다. <br>

- Quadratic form을 만족시키는 matrix $A$는 *symmetric* 하지 않는 경우를 포함하여 무수히 많다. <br>
그러나, 대칭의 위치에 해당하는 두 개의 off-diagonal element를 더하고 반으로 나누면 동일한 *symmetric*한 matrix $A$를 만들어낼 수 있다.

## 3. Definiteness
With quadratic form $q(\mathbf{x}) = \mathbf{x}^T A \mathbf{x}$, a real *symmetric* matrix $A$ is
$$
\begin{equation}
\begin{aligned}
    \textbf{positive definite} \ (A \succ 0) \quad &\text{ if } q(\mathbf{x}) > 0 \text{ for all } \mathbf{x} \neq 0 \in \mathbb{R} ^n \\
    \textbf{positive semi-definite} \ (A \succeq 0) \quad &\text{ if } q(\mathbf{x}) ≥ 0 \text{ for all } \mathbf{x} \neq 0 \in \mathbb{R} ^n \\
    \textbf{negative definite} \ (A \prec 0) \quad &\text{ if } q(\mathbf{x}) < 0 \text{ for all } \mathbf{x} \neq 0 \in \mathbb{R} ^n \\
    \textbf{negative semi-definite} \ (A \preceq 0) \quad &\text{ if } q(\mathbf{x}) ≤ 0 \text{ for all } \mathbf{x} \neq 0 \in \mathbb{R} ^n \\
    \textbf{indefinite} \quad &\text{ if } A \text{ is neither positive semi-definite nor negative semi-definite}  \\
\end{aligned}
\end{equation}
$$

- **Matrix $A$의 difinitness에 따라 quadratic form의 optimality가 결정된다.** <br>
$\text{if } A \succeq 0, \ q(\mathbf{x}) \text{ is convex and } \mathbf{x}=\mathbf{0} \text{ is global minimum}$ <br>
$\text{if } A \preceq 0, \ q(\mathbf{x}) \text{ is concave and } \mathbf{x}=\mathbf{0} \text{ is global maximum}$

- Matrix $A$의 **eigenvalue**의 부호를 통해 definiteness가 결정되기도 한다. <br>
$\mathbf{x} = P\mathbf{y} \ \text{ s.t. } P \text{ is regular}$ <br>
$\mathbf{x}^T A \mathbf{x} = (P\mathbf{y})^T A (Py) = \mathbf{y}^T P^T A P \mathbf{y} = \mathbf{y}^T (P^TAP)\mathbf{y} = \mathbf{y}^TD\mathbf{y} \quad \text{(Spectral decomposition)}$ <br>
$\mathbf{y}^TD\mathbf{y} = \sum_i \lambda_i y_i^2$ <br>

$$
\begin{equation}
\begin{aligned}
    \textbf{positive definite} \ (A \succ 0) \quad &\text{ iff all eigenvalue } \lambda_i > 0 \\
    \textbf{positive semi-definite} \ (A \succeq 0) \quad &\text{ iff all eigenvalue } \lambda_i ≥ 0 \\
    \textbf{negative definite} \ (A \prec 0) \quad &\text{ iff all eigenvalue } \lambda_i < 0 \\
    \textbf{negative semi-definite} \ (A \preceq 0) \quad &\text{ iff all eigenvalue } \lambda_i ≤ 0 \\
    \textbf{indefinite} \quad &\text{ iff some eigenvalue > 0 and other eigenvalue < 0} \\
\end{aligned}
\end{equation}
$$

- Positive definite 혹은 negative definite matrix는 역행렬이 존재한다. $(\because \ det(A) = \Pi_i \lambda_i \neq 0)$ <br>
역행렬의 eigenvalue는 원래 행렬의 eigenvalue의 역수이기 때문에 definiteness는 변하지 않는다.

- **Covariance matrix** <br>
$X = (X_1, \cdots, X_n)^T$에 대한 covariance matrix $C$ <br>
$C = E[(X - \mu_X)(X - \mu_X)^T] = E[XX^T] - \mu_X\mu_X^T$ <br>
$C = \frac{1}{n} \sum_i (X_i - \bar{X})(X_i - \bar{X})^T$ <br><br>
$$
\begin{equation}
\begin{aligned}
    \mathbf{y}^T C \mathbf{y} &= \mathbf{y}^T (\frac{1}{n} \sum_i (X_i - \bar{X})(X_i - \bar{X})^T) \mathbf{y} \\
    &= \frac{1}{n} \sum_i \mathbf{y}^T (X_i - \bar{X})(X_i - \bar{X})^T \mathbf{y} \\
    &= \frac{1}{n} \sum_i ((X_i - \bar{X})^T \mathbf{y})^T((X_i - \bar{X})^T \mathbf{y}) \\
    &= \frac{1}{n} \sum_i ((X_i - \bar{X})^T \mathbf{y})^2 ≥ 0 \\
\end{aligned}
\end{equation}
$$
<br>
따라서, covariance matrix는 positive semi-definite이다. <br>
