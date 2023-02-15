---
layout: article
title: Graphical Model
tags: Math_Base
sidebar:
  nav: docs-en
---

ex) Discrete Markov-Chain

![png](/images/graphical_files/1.jpg)

<!--more-->


## Data Dependency
Given $ \mathbf{X_t}, \mathbf{Y_t} $ is independent to every state
<br>

## Measurement update
$$
\begin{equation}
\begin{aligned}
    p(x_k | Y_k) &= p(x_k | Y_{k-1}, y_k) \\
    &∝ p(y_k | Y_{k-1}, x_k) p(x_k | Y_{k-1}) \\
    &= p(y_k | x_k) p(x_k | Y_{k-1})
\end{aligned}
\end{equation}
$$
