---
title: Cross validation
tags: MachineLearning_Base
---

<!--more-->

Cross validation에서 사용되는 `sklearn.model_selection.cross_val_score`는 `sklearn.model_selection.StratifiedKFold`으로 직접 구현하여 활용할 수 있다.


{% highlight python linenos %}
from sklearn.model_selection import StratifiedKFold
from sklearn.base import clone

scores1 = []
preds1  = []
cv = StratifiedKFold()  # default: cv=5
for idxs_train, idxs_test in cv.split(X, y):
    clone_model = clone(model)
    X_train_fold, y_train_fold = X[idxs_train], y[idxs_train]
    X_test_fold,  y_test_fold  = X[idxs_test], y[idxs_test]
    
    clone_model.fit(X_train_fold, y_train_fold)
    y_test_pred_fold = clone_model.predict(X_test_fold)
    scores1.append(accuracy_score(y_test_fold, y_test_pred_fold))
    preds1.extend(y_test_pred_fold)
{% endhighlight %}


{% highlight python linenos %}
from sklearn.model_selection import cross_val_score, cross_val_predict

clone_model = clone(model)
scores2 = cross_val_score(clone_model, X, y)  # default: cv=5, StratifiedKFolds
preds2  = cross_val_predict(clone_model, X, y)
print(np.all(scores1 == scores2), np.all(preds1 == preds2))  # preds 순서가 다를 수 있음
{% endhighlight %}

    True False
