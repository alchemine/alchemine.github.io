---
title: TensorBoard
tags: TensorFlow
---

# Remarks
본 포스팅은 **Hands-On Machine Learning with Scikit-Learn & TensorFlow ([Auérlien Géron](https://github.com/ageron/handson-ml), [박해선(역)](https://github.com/rickiepark/handson-ml), 한빛미디어)** 를 참고하여 작성되었습니다.

<!--more-->
---

# 1. Save summary
TensorBoard를 사용하기 위해선, 프로그램을 수정하여 **event file**이라는 로그 파일에 시각화하려는 데이터(**summary**)를 출력해야 한다. \
`tensorflow.keras.Callbacks.TensorBoard()` callback을 사용하면 이를 간단히 수행할 수 있다.

자세한 내용은 [Callbacks](https://alchemine.github.io/2020/03/01/callbacks#gsc.tab=0)를 참고

# 2. TensorBoard server
1. Default port \
`6006`
2. Command \
`$ tensorboard --logdir=LOGDIR` (`--bind_all`을 추가해야 동작하는 경우도 있음)
