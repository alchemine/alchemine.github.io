---
title: Prior selection in Bayesian linear regression
tags: Math_Base
aside:
  toc: true
---

<!--more-->

# I. Notations
$ \text{Target vector } Y = (Y_1, \cdots, Y_n)^T \in \mathbb{R}^n $ <br>
$ \text{Input vector (considered as const.) } X = (x_{ij}) \in \mathbb{R}^{n \times p} $ <br>
$ \text{Coefficient vector } \beta = (\beta_1, \cdots, \beta_p)^T \in \mathbb{R}^p $ <br>
$ \text{Variance } \sigma^2 \in \mathbb{R} $

# II. Model
$ Y \mid \beta, \sigma^2 \sim N_n(X\beta, \sigma^2 I_n) $

# III. Priors
## 1. Zellner's g-prior
### 1) Prior
$$
\beta \mid \sigma^2 \sim N_p(\beta_0, \color{blue}{g} \sigma^2 (X^T X)^{-1}) \quad\quad \cdots \quad\quad \color{blue}{g} \in \mathbb{R}^+ \\
\sigma^2 \sim \pi(\sigma^2) = \frac{1}{\sigma^2} \quad\quad \cdots \quad\quad \text{Jeffreys' prior}
$$

### 2) Posterior
$$
\beta \mid \sigma^2, y \sim N_p(\frac{1}{g+1}\beta_0 + \frac{g}{g+1}\hat{\beta}, \frac{g}{g+1}\sigma^2 (X^T X)^{-1}) \\
\sigma^2 \mid y \sim IG(\frac{n}{2}, \frac{n \hat{\sigma}^2}{2} + \frac{1}{2(g+1)} (\hat{\beta}-\beta_0)^TX^TX(\hat{\beta}-\beta_0))
$$
<br>
이처럼 posterior가 closed form으로 나타나 계산이 용이하기에 Bayesian linear regression에서 가장 많이 사용됩니다.

### 3) Choice of $g$
다음과 같은 3가지 문제가 발생하지 않도록 $g$를 선택해야 합니다. [^1] <br>

$ B(M_\gamma, M_{null}) = \frac{(1 + g)^{\frac{n - p_\gamma - 1}{2}}}{(1 + g[1 - R_\gamma^2])^{\frac{n - 1}{2}}} = (\frac{1 + g}{1 + g[1 - R_\gamma^2]})^{\frac{n-1}{2}} (1+g)^{\frac{-p_\gamma}{2}}$

1. $ B(M_\gamma, M_{null}) \to 0 \quad \text{as} \quad g \to \infty $ <br>
$g$가 커질수록 $ M_\gamma $와 무관하게 $ M_{null} $을 선호하는 문제가 발생할 수 있습니다. <br>
⇒ **Lindley's paradox**: $H_1$ 하에서의 prior balance($g$)를 너무 크게 만들어버리면 항상 $H_0$를 지지하게 되는 현상
<br><br>
2. $ B(M_\gamma, M_{null}) \to \infty \quad \text{as} \quad n \to \infty \quad \text{with a fixed } g $ <br>
$n$이 커질수록 $M_\gamma$와 무관하게 $M_\gamma$를 선호하는 문제가 발생할 수 있습니다. <br>
⇒ **Model selection consistency**: If $M_\ast$ is the true model, $ B(M_\ast, M_{null}) \to \infty \quad \text{as} \quad n \to \infty $ for any other $M_\gamma$
<br><br>
3. $ B(M_\gamma, M_{null}) \to (1+g)^\frac{n-p_\gamma-1}{2} \quad \text{as} \quad R_\gamma^2 \to 1 \quad \text{with a fixed } g $ <br>
$R_\gamma^2$이 1에 가까워질수록 Bayes factor가 발산하는 것이 아니라 특정값으로 수렴하는 문제가 발생할 수 있습니다. <br>
⇒ **Information paradox**: $R_\gamma^2$이 1에 수렴한다는 정보가 있음에도 Bayes factor가 계속 증가하지 않는 현상

<br>
이러한 문제가 발생하지 않도록 data에 의존하는 fully Bayesian approach로 $g$를 정할 수 있습니다. <br>
즉, hyp. $g$에 다시 prior(hyper prior)를 주는 방법입니다.
<br>

1. Information paradox를 막기 위해, 수렴값의 평균이 발산하도록 $g$의 분포를 정할 수 있습니다. <br>
$ \pi(g) = IG(\frac{1}{2}, \frac{n}{2}) \quad\quad \cdots \quad\quad \text{Zellner-Siow prior} $ <br>
$ \int (1+g)^\frac{n-p_\gamma-1}{2} \pi(g) \ dg = \infty $
<br><br>
2. 결과적으로 $\beta$의 분포는 Cauchy dist.를 따르게 되지만, 계산적인 이득을 고려하여 간단한 분포에서 계층적으로 sampling($IG → N$)하는 방법을 사용합니다. <br>
$ \pi(\beta) = \int \pi(\beta \mid g) \pi(g) \ dg = \text{Cauchy dist.}$
<br><br>
3. Marginal likelihood를 계산하기 위해 Laplace approx.가 필요하지만 unvariate($g$) case이기 때문에 큰 오차가 발생하지 않습니다. <br>
$ f(y) = \int f(y \mid g) \pi(g) \ dg $
<br><br>
4. 그 결과, 위의 3가지 문제에 모두 해당하지 않게됩니다.

## 2. Spike and slab priors
데이터의 개수 $n$보다 차원 $p$가 더 큰 경우, spike and slab prior가 가장 많이 사용됩니다. <br><br>

**High-dimensional setting** <br>
$ p \equiv p_n \to \infty \quad \text{as} \quad n \to \infty $ ($p \gg n$ 인 상황을 잘 근사해서 표현) <br>

**Sparse assumption in LR** <br>
$ \beta $ is sparse vector s.t. $ \Sigma_{j=1}^p I(\beta_j \neq 0) \leq s_0 = o(p) $ (대부분의 회귀계수가 0에 가깝다) <br>

### 1) Prior
$ \beta_j \stackrel{iid}{\sim} (1 - \pi_0)\delta_0 + \pi_0 g(\cdot) \quad\quad \cdots \quad\quad \delta_0: \text{spike, } g(\cdot): \text{slab, } \pi_0: \text{ratio of non-zero coefficient} $ <br>

$g$의 분포로 일반적으로 Normal dist.를 사용하거나 non-local prior를 사용할 수 있습니다. <br>
Posterior 계산을 용이하게 하기 위해 다음과 같이 hierarchical prior로 구성합니다. <br>

$$
\begin{equation}
\begin{aligned}
  \beta_j \mid Z_j = 0 &\stackrel{ind}{\sim} \delta_0 \\
  \beta_j \mid Z_j = 1 &\stackrel{ind}{\sim} g(\beta_j \mid \sigma^2) \\
  g(\beta_j \mid \sigma^2) &= N(\beta_j \mid 0, \sigma^2 \tau^2) \\
  Z_j &\stackrel{iid}{\sim} Ber(\pi_0) \\
  \sigma^2 &\sim IG(\gamma_1, \gamma_2)
\end{aligned}
\end{equation}
$$
<br>
추가적으로, $\pi_0$에 prior를 걸고 posterior sample을 얻으면 각 회귀계수가 0일 확률에 대해 말할 수 있습니다. $(1 - \pi_0)$

### 2) Posterior
$$
\begin{equation}
\begin{aligned}
  \pi(\beta, Z, \sigma^2 \mid y)
  &\propto f(y \mid \beta, Z, \sigma^2) \ \pi(\beta, Z, \sigma^2) \\
  &= f(y \mid \beta, Z, \sigma^2) \ \pi(\beta \mid Z, \sigma^2) \ \pi(Z, \sigma^2) \\
  &= f(y \mid \beta, Z, \sigma^2) \ \pi(\beta \mid Z, \sigma^2) \ \pi(Z) \ \pi(\sigma^2) \\
  &= N_n(Y \mid X\beta, \sigma^2 I_n) \ \Pi_{j: Z_i=0}I(\beta_j = 0) \ \Pi_{j: Z_i=1}g(\beta_j \mid \sigma^2) \ \Pi_j Ber(Z_j \mid \pi_0) \ IG(\sigma^2 \mid \gamma_1, \gamma_2)
\end{aligned}
\end{equation}
$$

### 3) Model selection
1. Notations <br>
Example in 4-dimensional case <br>
$$
  k = (1, 0, 0, 1) \\
  |k| = 2 \\
  \beta_k = (\beta_1, \beta_4) \\
  X_k = [n, |k|]
$$ <br>
2. Marginal posterior <br>
$$
\begin{equation}
\begin{aligned}
  \pi(Z=k \mid y)
  &\propto \iint \pi(Z=k, \beta, \sigma^2 \mid y) \ d\beta d\sigma^2 \\
  &\propto \ ... \\
  &\propto det(\tau^2 X_k^TX_k + I_{|k})^{-\frac{1}{2}} (\frac{\pi_0}{1-\pi_0})^{|k|} (\frac{1}{2} \tilde{R}_k + \gamma_2)^{-\frac{n}{2} + \gamma_1} \\
  \tilde{R}_k &= y^T \{ I_n - X_k (X_k^T X_k + \tau^{-2} I_{|k|})^{-1} X_k^T \} y
\end{aligned}
\end{equation}
$$
<br><br>
나름대로 계산이 깔끔하게(?) 나오긴 하지만, 실제론 계산량 때문에 이러한 방법을 거쳐서 sampling하기가 어렵습니다. <br>
MH algorithm을 사용할 수도 있지만 모수공간이 너무 넓기 때문에 적당히 탐험하기가 쉽지 않다는 문제점이 존재합니다. <br>
따라서, 근사적으로 posterior를 구하여 가장 많이 나온 값을 사용하거나(MAP), 중간값(Median)을 사용하는 방법을 주로 사용합니다. <br>
3. Select the final model <br>
3.1. MAP <br>
**Shotgun Stochastic Search (SSS) algorithm** <br>
$ k \subseteq {1, \cdots , p} $ <br>
$$
\begin{equation}
\begin{aligned}
  \text{Let }
  \Gamma_k^+ &= \{k \cup \{l\} &: l \in k^c \} \\
  \Gamma_k^- &= \{k \setminus \{j\} &: j \in k \} \\
  \Gamma_k^0 &= \{[k \setminus \{j\}] \cup \{l\} &: j \in k, \ l \in k^c \} \\
\end{aligned}
\end{equation}
$$ <br>
$ \text{Iterate processes below} $ <br>
$ \quad \text{1. Compute } \pi(k \mid y) \text{ for all } k^{(i)} \in \{ \Gamma_k^+, \Gamma_k^-, \Gamma_k^0 \} $ <br>
$ \quad \text{2. Sample } k^+, k^-, k^0 \text{ from } \Gamma_k^+, \Gamma_k^-, \Gamma_k^0 \text{ with prob. proportional to } \pi(k \mid y) $ <br>
$ \quad \text{3. Sample } k^{(i+1)} \text{ from } \{ k^+, k^-, k^0 \} \text{ with prob. proportional to } \{ \pi(k^+ \mid y), \pi(k^- \mid y), \pi(k^0 \mid y) \} $ <br><br>
3.2. Median probability model <br>
Inclusion prob. $ p_j = \pi(Z_j = 1 \mid y) $에 집중하는 방법으로 optimal predictive model로 알려져있고 MAP보다 일반적으로 선호되는 방법입니다. <br><br>
$ \hat{p_j} = \frac{1}{L} \Sigma_{l=1}^L Z_j^{(l)} $ : Sample mean (0 ~ 1) <br>
$ \text{If } \hat{p_j} > \frac{1}{2} \text{ then, include } \beta_j $ <br>
$ \text{If } \hat{p_j} ≤ \frac{1}{2} \text{ then, exclude } \beta_j $ <br>

---

[^1]: Bayes factor에 대해선, [Bayesian hypothesis testing/Bayes factor](https://alchemine.github.io/2019/12/09/bayes_test.html#4-bayes-factor)를 참조
