---
title: Rank factorization
tags: Math_Base
---

이번에 살펴볼 내용은 rank와 관련하여 행렬을 분해하는 방법인 **rank factorization** 입니다. <br>
자세한 내용은 [https://en.wikipedia.org/wiki/Rank_factorization](https://en.wikipedia.org/wiki/Rank_factorization ) 을 참조하세요.
<br>

*For all* $A$, there are $B$ and $C$ such that <br> - $A = BC$
<br> - $A \in \mathbb{R^{m \times n}}$, *rank $A$ = $r$*
<br> - $B \in \mathbb{R^{m \times r}}$, *rank $B$ = $r$*
<br> - $C \in \mathbb{R^{r \times n}}$, *rank $C$ = $r$*
{:.success}

<!--more-->

1. *Let $\mathbf{b}_i \doteq$ i'th basis of $\mathbb{C}(A)$
<br> $\mathbf{a}_j \doteq$ j'th column vector of $A$*

2. *$\mathbf{a}_j = \sum_{i=1}^r c_{ij} \mathbf{b}_i$*
<br>
$$
\mathbf{a}_j =
\begin{align*}
\begin{pmatrix}
\\
\mathbf{b}_1 & \cdots & \mathbf{b}_r\\
\\
\end{pmatrix}
\begin{pmatrix}
c_{11}\\
\vdots\\
c_{r1}\\
\end{pmatrix}
\end{align*}
$$

3. $A = BC$ <br>
$$
\begin{aligned}
A =
\begin{pmatrix}
\\
\mathbf{a}_1 & \cdots & \mathbf{a}_n\\
\\
\end{pmatrix} =
\begin{pmatrix}
\\
\mathbf{b}_1 & \cdots & \mathbf{b}_r\\
\\
\end{pmatrix}
\begin{pmatrix}
c_{11} & \cdots & c_{1n}\\
\vdots & \ddots & \vdots\\
c_{r1} & \cdots & c_{rn}\\
\end{pmatrix}
= BC
\end{aligned}
$$
