---
title: Bayesian hypothesis testing
tags: Math_Base
aside:
  toc: true
---

<!--more-->

# 1. Hypothesis testing problem
$ H_0 : \theta \in \Theta_0 \quad\quad \text{vs} \quad\quad H_1: \theta \in \Theta_1 \quad\quad (\Theta_0 \uplus \Theta_1 = \Theta = \text{whole parameter space})$

# 2. Bayesian approach
1. Calculate the posterior prob. for each model ($\Theta_0, \Theta_1$): $ \pi(H_0 \mid x), \pi(H_1 \mid x) $
2. Support the hypothesis that has larger posterior prob.

# 3. Calculate posterior
1. Posterior $ \pi(H_i | x) $ <br>
$$
\begin{equation}
\begin{aligned}
  \pi(H_i | x)
  &\propto p(H_i) \color{red}{f(x | H_i)} \\
  &= \color{blue}{\pi_i} f(x | H_i) \quad\quad \cdots \quad\quad \color{blue}{\pi_i} \equiv p(H_i) \\
  \color{red}{f(x | H_i)}
  &= \int_{\theta \in \Theta_i} f(x | \theta, H_i) \pi(\theta | H_i) d\theta \\
  &= \int_{\theta \in \Theta_i} f(x | \theta) \pi(\theta | H_i) d\theta \quad\quad \cdots \quad\quad \text{Assume that } f(x | \theta) = f(x | \theta, H_i) \\
  &= \int_{\theta \in \Theta_i} f(x | \theta) \color{blue}{g_i(\theta)} d\theta \quad\quad \cdots \quad\quad \color{blue}{g_i(\theta)} \equiv \pi(\theta | H_i) \\
\end{aligned}
\end{equation}
$$
2. Compare posterior prob. <br>
$$
\pi(H_0 \mid x)
= \frac{f(x, H_0)}{f(x, H_0) + f(x, H_1)}
= \frac{\pi_0 \int_{\theta \in \Theta_0} f(x | \theta) g_0(\theta) d\theta}{\pi_0 \int_{\theta \in \Theta_0} f(x | \theta) g_0(\theta) d\theta + \pi_1 \int_{\theta \in \Theta_1} f(x | \theta) g_1(\theta) d\theta} \\
\pi(H_1 \mid x)
= \frac{f(x, H_1)}{f(x, H_0) + f(x, H_1)}
= \frac{\pi_1 \int_{\theta \in \Theta_1} f(x | \theta) g_1(\theta) d\theta}{\pi_0 \int_{\theta \in \Theta_0} f(x | \theta) g_0(\theta) d\theta + \pi_1 \int_{\theta \in \Theta_1} f(x | \theta) g_1(\theta) d\theta}
$$
Support $\text{argmax}_i \pi(H_i \mid x)$

# 4. Bayes factor
1. Prior odds <br>
$ \frac{\pi_0}{\pi_1} $

2. Posterior odds <br>
$ \frac{\pi(H_0 \mid x)}{\pi(H_1 \mid x)} $

3. Bayes factor <br>
$ B_{01}(x) = \frac{\pi(H_0 \mid x)}{\pi(H_1 \mid x)} \times \frac{\pi_1}{\pi_0} = \frac{f(x \mid H_0)}{f(x \mid H_1)} $
$ B_{10}(x) = \frac{1}{B_{01}(x)} \quad\quad \text{(symmetric)} $ <br>
$ f(x \mid H_i) $ : the amount of evidence that the data $x$ supports hypothesis $H_i$
