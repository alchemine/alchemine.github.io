---
title: Neural Network Hyperparameter Tuning Guideline
tags: MachineLearning_Base
---

<!--more-->

# 1. Number of hidden layers
1. Transfer learning
2. 1, 2개부터 시작하여 overfitting이 생길 때까지 점진적으로 늘려보기
3. Layer의 개수를 늘리는 것이 neuron의 개수를 늘리는 것보다 이득이 많음

## 1.1 Parameter efficiency
Hidden layer의 개수가 많을수록, 복잡한 함수를 modeling하는 데 필요한 neuron의 개수가 적음

**[Cybenko's theorem(시벤코 정리, 일반 근사 이론)](https://ko.wikipedia.org/wiki/%EC%8B%9C%EB%B2%A4%EC%BD%94_%EC%A0%95%EB%A6%AC)** \
Node의 개수가 충분한 hidden layer 하나로 구성된 MLP는 어떤 함수도 근사할 수 있다.
{:.info}

## 1.2 Hierarchical structure of data
- Data는 **계층 구조**로 구성되어 있는 경우가 많다.
- Hidden layer들은 data에 내재된 계층의 정보를 modeling할 수 있다.
  1. Low hidden layer: Low level structure \
  여러 방향이나 모양의 선 등
  2. Middle hidden layer: Middle level structure(composite of low level structure) \
  여러 개의 선으로 구성된 도형(사각형, 원) 등
  3. High hidden layer: High level structure(composite of middle level structure) \
  여러 개의 구성요소로 이루어진 얼굴 등
- 계층 구조는 NN가 빨리 수렴하도록 도와줄 뿐만 아니라, 새로운 data에 대한 **일반화 성능**을 향상시킨다.
- High level structure만을 학습하는 **transfer learning(전이 학습)** 가능


# 2. Number of neurons
1. Many neurons(low) → a few neurons(high) \
**Low level의 많은 특성들**이 **high level의 적은 특성**으로 합쳐질 수 있음
2. Equal number of neurons \
1과 성능에서 큰 차이가 없음. 단, **첫 번째 hidden layer는 neuron의 개수를 크게 하는 것이 좋음**
3. Stretch pants
**Strecth pants** \
필요한 것보다 더 많은 layer와 neuron을 선택하고 overfitting되지 않도록 earlystopping, regularization을 사용하는 것이 간단하고 효과적임
{:.success}


# 3. Learning rate
1. 일반적으로 최적의 learning rate는 최대 learning rate(발산)의 절반 정도
2. `scipy.stats.reciprocal(1e-5, 1e-1)` (Log-uniform, reciprocal 분포를 사용하여 grid search)


# 4. Batch size
## 4.1 Big batchsize
1. HW 가속기를 효율적으로 활용가능
2. 학습 초기에 불안정하게 훈련될 수 있음(?)
3. Learning rate warming up(learning rate를 점점 증가시킴)을 사용하면 큰 batchsize 사용 가능

## 4.2 Small batchsize
1. 일반화 성능이 높은 model을 선택
2. LeCun옹: 32 이하의 batchsize를 사용해라


# Example
[A Neural Network Playground](playground.tensorflow.org)는 다양한 hyperparameter의 역할을 이해하는 데 도움이 된다.
