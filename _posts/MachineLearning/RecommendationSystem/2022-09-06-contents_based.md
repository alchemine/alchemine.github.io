---
title: Contents-based Recommendation Systems
tags: RecommendationSystem
---

<!--more-->

# 1. Contents-based RS
**Contensts-based Recommendation Systems** \
과거에 사용자가 선호했던 것과 **유사한** item을 추천하는 모델.
(The system learns to recommend items that are similar to the ones that the user liked in the past.)
{:.success}

![contents-based RS 1](/deprecated/assets/contents-based%20RS%201.jpg)


## 1) Algorithm
<!-- 1. **CONTEXT ANALYZER: Extract features** \
Unstructured items를 structured item representation으로 변환하는 전처리 과정
2. **FEEDBACK: Collect feedback from the active user** \
Item에 대한 사용자의 반응(reactions, annotations, feedback)을 가공하여 사용자의 profile을 생성
    - Explicit feedback \
      사용자에게 직접 item을 평가하도록 요구하여 얻어진 반응
    - Implicit feedback \
      사용자의 활동을 분석하고 모니터링하여 얻어진 반응
3. **PROFILE LEARNER: Train <representation, ratings>** \
Active user $u_a$의 profile을 구축하기 위해, <$I_k$, $r_k$> 데이터셋을 학습
    - $I_k$: Item $k$에 대한 representation
    - $r_k$: $u_a$가 평가한 item $k$의 점수
4. **FILTERING COMPONENT: Predict whether it is likely to be of interest for the active user** -->
1. **Extract features** \
Unstructured items를 structured item representation으로 변환하는 전처리 과정
2. **Compute similarity** \
Item representation 간의 유사도를 계산
    - Similarity: Euclidean, cosine, inner product, Pearson, Jaccard, etc


---

#### Reference
1. [[토크ON세미나] 추천시스템 분석 입문하기](https://www.youtube.com/playlist?list=PL9mhQYIlKEhdkOVTZWJJIy8rv6rQaZNNc)
2. [Recommendation Systems Handbook(Francesco Ricci *et al.*)](https://www.cse.iitk.ac.in/users/nsrivast/HCC/Recommender_systems_handbook.pdf)
