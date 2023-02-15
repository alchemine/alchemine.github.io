---
title: Functional API
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

scaler = StandardScaler()
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
from tensorflow.keras.layers import Input, Dense, Concatenate

input_  = Input(shape=X_train[0].shape)
hidden1 = Dense(30, activation='relu')(input_)
hidden2 = Dense(30, activation='relu')(hidden1)
concat  = Concatenate()([input_, hidden2])  # default: axis=-1
output  = Dense(1)(concat)
model   = Model(inputs=[input_], outputs=[output])
model.summary()
```

    Model: "model"
    __________________________________________________________________________________________________
    Layer (type)                    Output Shape         Param #     Connected to
    ==================================================================================================
    input_1 (InputLayer)            [(None, 8)]          0
    __________________________________________________________________________________________________
    dense (Dense)                   (None, 30)           270         input_1[0][0]
    __________________________________________________________________________________________________
    dense_1 (Dense)                 (None, 30)           930         dense[0][0]
    __________________________________________________________________________________________________
    concatenate (Concatenate)       (None, 38)           0           input_1[0][0]
                                                                     dense_1[0][0]
    __________________________________________________________________________________________________
    dense_2 (Dense)                 (None, 1)            39          concatenate[0][0]
    ==================================================================================================
    Total params: 1,239
    Trainable params: 1,239
    Non-trainable params: 0
    __________________________________________________________________________________________________



```python
input1  = Input(shape=X_train[0].shape)
input2  = Input(shape=X_train[0].shape)
hidden1 = Dense(30, activation='relu')(input2)
hidden2 = Dense(input1.shape[1], activation='relu')(hidden1)
concat  = Concatenate()([input1, hidden2])
output  = Dense(1)(concat)
model   = Model(inputs=[input1, input2], outputs=[output])
model.summary()
```

    Model: "model_1"
    __________________________________________________________________________________________________
    Layer (type)                    Output Shape         Param #     Connected to
    ==================================================================================================
    input_3 (InputLayer)            [(None, 8)]          0
    __________________________________________________________________________________________________
    dense_3 (Dense)                 (None, 30)           270         input_3[0][0]
    __________________________________________________________________________________________________
    input_2 (InputLayer)            [(None, 8)]          0
    __________________________________________________________________________________________________
    dense_4 (Dense)                 (None, 8)            248         dense_3[0][0]
    __________________________________________________________________________________________________
    concatenate_1 (Concatenate)     (None, 16)           0           input_2[0][0]
                                                                     dense_4[0][0]
    __________________________________________________________________________________________________
    dense_5 (Dense)                 (None, 1)            17          concatenate_1[0][0]
    ==================================================================================================
    Total params: 535
    Trainable params: 535
    Non-trainable params: 0
    __________________________________________________________________________________________________



```python
input1  = Input(shape=X_train_A[0].shape)
input2  = Input(shape=X_train_B[0].shape)
hidden1 = Dense(30, activation='relu')(input2)
hidden2 = Dense(input1.shape[1], activation='relu')(hidden1)
concat  = Concatenate()([input1, hidden2])
output1 = Dense(1, name='main_output')(concat)  # prediction
output2 = Dense(1, name='aux_output')(hidden2)  # regularization
model   = Model(inputs=[input1, input2], outputs=[output1, output2])
model.summary()

model.compile(loss=['mse', 'mse'], loss_weights=[0.9, 0.1], optimizer='sgd')
```

    Model: "model_2"
    __________________________________________________________________________________________________
    Layer (type)                    Output Shape         Param #     Connected to
    ==================================================================================================
    input_5 (InputLayer)            [(None, 6)]          0
    __________________________________________________________________________________________________
    dense_6 (Dense)                 (None, 30)           210         input_5[0][0]
    __________________________________________________________________________________________________
    input_4 (InputLayer)            [(None, 5)]          0
    __________________________________________________________________________________________________
    dense_7 (Dense)                 (None, 5)            155         dense_6[0][0]
    __________________________________________________________________________________________________
    concatenate_2 (Concatenate)     (None, 10)           0           input_4[0][0]
                                                                     dense_7[0][0]
    __________________________________________________________________________________________________
    main_output (Dense)             (None, 1)            11          concatenate_2[0][0]
    __________________________________________________________________________________________________
    aux_output (Dense)              (None, 1)            6           dense_7[0][0]
    ==================================================================================================
    Total params: 382
    Trainable params: 382
    Non-trainable params: 0
    __________________________________________________________________________________________________


# 3. Training & evaluation


```python
history  = model.fit((X_train_A, X_train_B), (y_train, y_train), validation_data=((X_valid_A, X_valid_B), (y_valid, y_valid)), epochs=5)
model.evaluate((X_test_A, X_test_B), (y_test, y_test))
```

    Epoch 1/5
    363/363 [==============================] - 2s 3ms/step - loss: 1.0018 - main_output_loss: 0.8799 - aux_output_loss: 2.0994 - val_loss: 0.6804 - val_main_output_loss: 0.5767 - val_aux_output_loss: 1.6134
    Epoch 2/5
    363/363 [==============================] - 1s 3ms/step - loss: 0.6081 - main_output_loss: 0.5295 - aux_output_loss: 1.3159 - val_loss: 0.5735 - val_main_output_loss: 0.5018 - val_aux_output_loss: 1.2184
    Epoch 3/5
    363/363 [==============================] - 1s 3ms/step - loss: 0.5320 - main_output_loss: 0.4768 - aux_output_loss: 1.0281 - val_loss: 0.5089 - val_main_output_loss: 0.4576 - val_aux_output_loss: 0.9711
    Epoch 4/5
    363/363 [==============================] - 1s 3ms/step - loss: 0.4957 - main_output_loss: 0.4533 - aux_output_loss: 0.8770 - val_loss: 0.4821 - val_main_output_loss: 0.4417 - val_aux_output_loss: 0.8451
    Epoch 5/5
    363/363 [==============================] - 1s 3ms/step - loss: 0.4843 - main_output_loss: 0.4505 - aux_output_loss: 0.7890 - val_loss: 0.5891 - val_main_output_loss: 0.5624 - val_aux_output_loss: 0.8295
    162/162 [==============================] - 0s 1ms/step - loss: 0.6837 - main_output_loss: 0.6692 - aux_output_loss: 0.8139

    [0.6837040781974792, 0.6692395806312561, 0.8138824105262756]
