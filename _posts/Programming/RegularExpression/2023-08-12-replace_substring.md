---
title: Replace Substring
tags: RegularExpression
---

<!--more-->

```python
import re

s = "123ABCtarget tar get targetDEF456 789GHI"
p = r"[^\s]*target[^\s]*"

rst = re.sub(p, r"_target_", s)
rst
```




    '_target_ tar get _target_ 789GHI'
