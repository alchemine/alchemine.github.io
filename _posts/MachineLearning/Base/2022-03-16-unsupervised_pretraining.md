---
title: Unsupervised Pretraining
tags: MachineLearning_Base
---

# Remarks
본 포스팅은 **Hands-On Machine Learning with Scikit-Learn & TensorFlow ([Auérlien Géron](https://github.com/ageron/handson-ml), [박해선(역)](https://github.com/rickiepark/handson-ml), 한빛미디어)** 를 참고하여 작성되었습니다.

<!--more-->
---

**Unsupervised Pretraining** \
레이블되지 않은 데이터로 NN의 일부를 학습시키는 unsupervised learning
{:.success}


# Algorithm
1. **Unsupervised learning(latent variable modeling)** \
AutoEncoder, GAN과 같은 generative model로 unlabeled data를 학습시킨다.
2. **Select latent variable model** \
학습된 layers 중 latent variable model을 선택한다.
    - AutoEncoder의 하위 layers(encoder)
    - GAN의 discriminator의 하위 layers
3. **Supervised learning** \
선택된 layers 위에 output layer를 쌓고 labeled data로 학습시킨다.
