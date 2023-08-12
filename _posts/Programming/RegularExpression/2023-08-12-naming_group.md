---
title: Naming Group
tags: RegularExpression
---

<!--more-->

```python
import re

s = "123ABCtarget tar get targetDEF456 789GHI"
p = r"(?P<prefix>[^\s]*)target(?P<suffix>[^\s]*)"

rst1 = re.sub(p, r'\g<1>\g<2>', s)
rst2 = re.sub(p, r'\g<prefix>\g<suffix>', s)
print(rst1)
print(rst2)
```

    123ABC tar get DEF456 789GHI
    123ABC tar get DEF456 789GHI