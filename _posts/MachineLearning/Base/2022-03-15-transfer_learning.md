---
title: Transfer Learning
tags: MachineLearning_Base
aside:
  toc: True
---

# Remarks
본 포스팅은 **Hands-On Machine Learning with Scikit-Learn & TensorFlow ([Auérlien Géron](https://github.com/ageron/handson-ml), [박해선(역)](https://github.com/rickiepark/handson-ml), 한빛미디어)** 를 참고하여 작성되었습니다.

<!--more-->
---

**Transfer Learning** \
해결하고자 하는 문제와 비슷한 유형의 문제를 학습한 network의 하위 layer를 재사용하는 학습방법
{:.success}


# 1. Algorithm
1. 유사한 문제를 학습한 network를 가져옴
2. 문제에 맞게 상위 layer의 구조를 수정
3. 재사용하는 하위 layer가 학습되지 않도록 동결(`trainable=False`)
4. 맨 위의 한두개의 hidden layer의 동결을 해제하고 학습하면서 성능이 향상되는지 확인
    - 학습 초기에는 작은 learning rate를 사용


# 2. Examples
1. 복잡한 계층구조로 이루어진 image를 학습하는 **CNN**과 시계열 데이터를 다루는 **NLP** 문제에서 transfer learning은 필수!
2. Google이 운영하는 [TensorFlow Hub](https://www.tensorflow.org/hub?hl=ko)에 많은 pretrained model들이 있으니 먼저 확인해보자 ([TensorFlow Resource](https://www.tensorflow.org/resouces), [awesome-tensorflow](https://github.com/jtoy/awesome-tensorflow)도 참고)


# 3. Code
```
# 1. Load pretrained model
pretrained_model = keras.models.clone_model(keras.models.load_model("pretrained.h5"))  # deep copy
model            = keras.models.Sequential(pretrained_model[:-1])  # except output layer
model.add(keras.layers.Dense(1, activation='sigmoid'))


# 2. Train except pretrained layers
for layer in model.layers[:-1]:
  layer.trainable = False
model.compile(..)
model.fit(..)


# 3. Train including pretrained layers
for layer in model.layers[:-1]:
  layer.trainable = True
model.compile(..)
model.fit(..)  # learning rate is less than before
```
