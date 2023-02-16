---
title: Custom Loss
tags: TensorFlow
---

<!--more-->

{% highlight python linenos %}
class CondLoss(tf.keras.losses.Loss):
    def __init__(self, loss_fn, marked_target_value, **kwargs):
        self.loss_fn = loss_fn
        self.marked_target_value = marked_target_value
        super().__init__(**kwargs)
    def call(self, y_true, y_pred):
        # y_true, y_pred: [B, S, D]
        assert y_true.shape == y_pred.shape, f'Shape mismatch for output and ground truth array {y_true.shape} and {y_pred.shape}'

        _, S, D = y_true.shape  # Batch, Sequence, Dim of features
        y_true = tf.reshape(y_true, (-1, D))
        y_pred = tf.reshape(y_pred, (-1, D))

        idxs_valid = (y_pred[:, -1] != self.marked_target_value)
        y_true_valid, y_pred_valid = y_true[idxs_valid], y_pred[idxs_valid]
        error = y_true_valid - y_pred_valid
        if self.loss_fn == 'rmse':
            return tf.sqrt(tf.reduce_mean(tf.square(error)))
        elif self.loss_fn == 'mse':
            return tf.reduce_mean(tf.square(error))
        elif self.loss_fn == 'mae':
            return tf.reduce_mean(tf.abs(error))
        else:
            raise NotImplementedError

model.compile(optimizer='adam', loss=CondLoss('rmse', -9999), metrics=['mae'])
{% endhighlight %}
