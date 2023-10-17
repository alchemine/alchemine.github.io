---
title: Active learning
tags: MachineLearning_Base
---

**Active learning(능동 학습)** \
알고리즘이 전문가에게 특정 샘플의 레이블을 요청하여 모델과 훈련 세트를 지속적으로 향상시키는 방법
{:.success}

<!--more-->

# 1. Uncertainty sampling
1. 레이블된 학습 데이터로 모델을 **학습**
2. 모델을 사용하여 레이블되지 않은 모든 데이터에 대한 **예측**을 수행
3. **불확실성**이 높은(추정 확률이 낮은) 샘플의 레이블을 전문가에게 **요청**하고 레이블을 붙임
4. Step 1~3을 반복
