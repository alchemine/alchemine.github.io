---
title: Simple regression
tags: TensorFlow
aside:
  toc: True
---

<!--more-->


# Import packages


```python
import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
plt.style.use('ggplot')

import tensorflow as tf
from tensorflow import keras
```

# 1. Load dataset


```python
from sklearn.datasets import fetch_california_housing
from sklearn.model_selection import train_test_split
from sklearn.preprocessing import StandardScaler

housing = fetch_california_housing()
X_train_full, X_test, y_train_full, y_test = train_test_split(housing.data, housing.target)
X_train, X_valid, y_train, y_valid         = train_test_split(X_train_full, y_train_full)
```

# 2. Preprocessing


```python
scaler  = StandardScaler()
X_train = scaler.fit_transform(X_train)
X_valid = scaler.transform(X_valid)
X_test  = scaler.transform(X_test)
```

# 3. Modeling


```python
from tensorflow.keras.models import Sequential
from tensorflow.keras.layers import Dense
from tensorflow_addons.metrics import RSquare

model = Sequential([
    Dense(30, input_shape=X_train[0].shape, activation='relu'),
    Dense(30, activation='relu'),
    Dense(1,)
])
model.compile(loss='mse', optimizer='sgd', metrics=[RSquare(y_shape=(1,))])
model.summary()
```

    Model: "sequential"
    _________________________________________________________________
    Layer (type)                 Output Shape              Param #
    =================================================================
    dense (Dense)                (None, 30)                270
    _________________________________________________________________
    dense_1 (Dense)              (None, 30)                930
    _________________________________________________________________
    dense_2 (Dense)              (None, 1)                 31
    =================================================================
    Total params: 1,231
    Trainable params: 1,231
    Non-trainable params: 0
    _________________________________________________________________


# 4. Training


```python
history  = model.fit(X_train, y_train, epochs=5, validation_data=(X_valid, y_valid))
pd.DataFrame(history.history).plot(figsize=(20, 5), grid=True, xlabel='epoch', ylabel='score');
```

    Epoch 1/5
    363/363 [==============================] - 1s 2ms/step - loss: 0.7642 - r_square: 0.4276 - val_loss: 0.4874 - val_r_square: 0.6198
    Epoch 2/5
    363/363 [==============================] - 1s 2ms/step - loss: 0.6431 - r_square: 0.5183 - val_loss: 0.4428 - val_r_square: 0.6546
    Epoch 3/5
    363/363 [==============================] - 1s 2ms/step - loss: 0.4648 - r_square: 0.6519 - val_loss: 0.4278 - val_r_square: 0.6663
    Epoch 4/5
    363/363 [==============================] - 1s 2ms/step - loss: 0.4545 - r_square: 0.6596 - val_loss: 0.4108 - val_r_square: 0.6795
    Epoch 5/5
    363/363 [==============================] - 1s 2ms/step - loss: 0.4226 - r_square: 0.6835 - val_loss: 0.3843 - val_r_square: 0.7002




![png](/deprecated/images/2022-03-11-tf-regression/output_9_1.png)



# 5. Evaluation


```python
model.evaluate(X_test, y_test)
```

    162/162 [==============================] - 0s 1ms/step - loss: 0.4340 - r_square: 0.6810
    [0.4340178668498993, 0.6809782385826111]




```python
X_new = X_test[:3]
y_pred = model.predict(X_new);  y_pred
```




    array([[2.2586539],
           [2.8899837],
           [2.7636592]], dtype=float32)
