---
title: Multiple inputs, outputs
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

# 1. Load dataset & preprocessing


```python
from sklearn.datasets import fetch_california_housing
from sklearn.model_selection import train_test_split
from sklearn.preprocessing import StandardScaler

housing = fetch_california_housing()
X_train_full, X_test, y_train_full, y_test = train_test_split(housing.data, housing.target)
X_train, X_valid, y_train, y_valid         = train_test_split(X_train_full, y_train_full)

scaler  = StandardScaler()
X_train = scaler.fit_transform(X_train)
X_valid = scaler.transform(X_valid)
X_test  = scaler.transform(X_test)

X_train_A, X_train_B = X_train[:, :5], X_train[:, 2:]
X_valid_A, X_valid_B = X_valid[:, :5], X_valid[:, 2:]
X_test_A,  X_test_B  = X_test[:, :5],  X_test[:, 2:]
X_new_A,   X_new_B   = X_test_A[:3],   X_test_B[:3]
```

# 2. Modeling


```python
from tensorflow.keras import Model
from tensorflow.keras.layers import Dense, Concatenate
from tensorflow_addons.metrics import RSquare

class WideAndDeepModel(Model):
    def __init__(self, units=30, activation='relu', **kwargs):
        super().__init__(**kwargs)
        self.hidden1 = Dense(units, activation=activation)
        self.hidden2 = Dense(units, activation=activation)
        self.main_output = Dense(1)
        self.aux_output  = Dense(1)
    def call(self, inputs):
        input_A, input_B = inputs
        hidden1 = self.hidden1(input_B)
        hidden2 = self.hidden2(hidden1)
        concat  = Concatenate()([input_A, hidden2])
        main_output = self.main_output(concat)
        aux_output  = self.aux_output(hidden2)
        return main_output, aux_output

model = WideAndDeepModel()
model.compile(loss='mse', optimizer='sgd', metrics=[RSquare(y_shape=(1,))])
# model.summary()  # subclass API는 summary() 불가
```

# 3. Training


```python
history = model.fit([X_train_A, X_train_B], [y_train, y_train], epochs=5, validation_data=([X_valid_A, X_valid_B], [y_valid, y_valid]))
pd.DataFrame(history.history).plot(figsize=(20, 5), grid=True, xlabel='epoch', ylabel='score');
```

    Epoch 1/5
    363/363 [==============================] - 3s 5ms/step - loss: 1.7983 - output_1_loss: 0.7166 - output_2_loss: 1.0817 - output_1_r_square: 0.4640 - output_2_r_square: 0.1909 - val_loss: 1.1375 - val_output_1_loss: 0.4818 - val_output_2_loss: 0.6557 - val_output_1_r_square: 0.6405 - val_output_2_r_square: 0.5108
    Epoch 2/5
    363/363 [==============================] - 2s 4ms/step - loss: 1.0727 - output_1_loss: 0.4692 - output_2_loss: 0.6035 - output_1_r_square: 0.6491 - output_2_r_square: 0.5486 - val_loss: 1.0769 - val_output_1_loss: 0.4757 - val_output_2_loss: 0.6011 - val_output_1_r_square: 0.6450 - val_output_2_r_square: 0.5515
    Epoch 3/5
    363/363 [==============================] - 2s 4ms/step - loss: 1.0806 - output_1_loss: 0.5072 - output_2_loss: 0.5735 - output_1_r_square: 0.6207 - output_2_r_square: 0.5710 - val_loss: 1.0273 - val_output_1_loss: 0.4612 - val_output_2_loss: 0.5661 - val_output_1_r_square: 0.6559 - val_output_2_r_square: 0.5776
    Epoch 4/5
    363/363 [==============================] - 2s 4ms/step - loss: 1.2061 - output_1_loss: 0.6781 - output_2_loss: 0.5279 - output_1_r_square: 0.4928 - output_2_r_square: 0.6051 - val_loss: 0.9958 - val_output_1_loss: 0.4461 - val_output_2_loss: 0.5496 - val_output_1_r_square: 0.6671 - val_output_2_r_square: 0.5899
    Epoch 5/5
    363/363 [==============================] - 2s 4ms/step - loss: 1.2297 - output_1_loss: 0.5375 - output_2_loss: 0.6921 - output_1_r_square: 0.5979 - output_2_r_square: 0.4823 - val_loss: 0.9707 - val_output_1_loss: 0.4188 - val_output_2_loss: 0.5519 - val_output_1_r_square: 0.6875 - val_output_2_r_square: 0.5882




![png](/deprecated/images/2022-03-11-tf-subclass_api/output_7_1.png)



# 4. Evaluation


```python
model.evaluate([X_test_A, X_test_B], [y_test, y_test])
```

    162/162 [==============================] - 0s 3ms/step - loss: 2.4178 - output_1_loss: 1.1732 - output_2_loss: 1.2447 - output_1_r_square: 0.1064 - output_2_r_square: 0.0519

    [2.417813777923584,
     1.1731566190719604,
     1.2446565628051758,
     0.10637742280960083,
     0.051914215087890625]




```python
y_pred = model.predict([X_new_A, X_new_B]);  y_pred
```




    (array([[1.2351167],
            [1.9935203],
            [4.297159 ]], dtype=float32),
     array([[0.90587264],
            [2.0000696 ],
            [3.281421  ]], dtype=float32))
