---
title: k-means clustering(Lloyd-Forgy algorithm)
tags: MachineLearning_Base
---

<!--more-->

# 1. Algorithm
1. **Initialize centroid** \
$k$개의 centroid를 초기화
    - **Advance 1: k-means++** \
      서로 멀리 떨어진 centroid로 초기화 → optimum solution으로 수렴 가능성 증가
2. **Update label** \
각 sample에 대하여 가장 가까운 centroid의 label을 할당
    - **Advance 2: Triangle inequality** \
    불필요한 거리 계산을 생략 → 속도 증가
3. **Update centroid** \
동일한 label을 가진 sample들에 대한 centroid를 update
4. **Repeat: centroid** \
Centroid가 수렴할 때까지 Step 1~3 반복
5. **Repeat: inertia** \
Step 1~4 를 반복하고 **inertia 값이 가장 작은 결과값**을 반환

# 2. Pros and cons
1. Pros
    - 속도가 빠름
    - 확장이 용이
2. Cons
    - 크기/밀집도가 다른 cluster에 부적합
    - 구형이 아닌 cluster에 부적합

## 3. Features
1. Distance 기반 algorithm이므로, scaling은 필수

## 4. Inertia
$\text{Inertia} = \frac{1}{n} \sum_i || x_i - \text{centroid}(x_i)||^2$
{:.success}

# 5. Hyperparameter tuning
## 5.1 $k$: number of clusters
1. Inertia \
$k$가 커질수록 inertia가 작아지기 때문에 metric으로 부적합
2. **Silhouette score** \
$$
\text{Silhouette score} = \frac{1}{n} \sum_i \text{Silhouette coefficient}_i \\
\text{Silhouette coefficient}_i = \frac{b_i-a_i}{max(a_i, b_i)} \\
a_i = \frac{1}{n} \sum_{x_j \in \text{cluster}(x_i)} ( x_j - x_i ) : \text{동일한 cluster의 sample들과의 평균 거리} \\
b_i = \frac{1}{n} \sum_{x_j \in \text{nearest cluster}(x_i)} ( x_j - x_i ) : \text{가장 가까운 cluster의 sample들과의 평균 거리}
$$
{:.success}
  - $ \text{Silhouette score} \in [0, 1]$
  - **큰 $ \text{Silhouette score}(x_i)$ → $x_i$가 cluster에 잘 속해 있고, 다른 cluster와 멀리 떨어져 있음**
  - **Silhouette diagram**을 보고 판단하는 것이 바람직함 (모든 cluster의 너비가 넓고, silhouette coefficient가 클수록 좋음)
