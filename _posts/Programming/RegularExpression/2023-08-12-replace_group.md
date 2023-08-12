---
title: Replace Group
tags: RegularExpression
---

<!--more-->

```python
import re

s = "123ABCtarget tar get targetDEF456 789GHI"
p = r"([^\s]*)target([^\s]*)"

rst = re.sub(p, r'\g<1>\g<2>', s)
rst
```

    '123ABC tar get DEF456 789GHI'