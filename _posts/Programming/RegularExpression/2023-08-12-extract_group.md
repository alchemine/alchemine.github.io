---
title: Extract Group
tags: RegularExpression
---

<!--more-->

```python
import re

s = "123ABCtarget tar get targetDEF456 789GHI"
p = r"([^\s]*)target([^\s]*)"

rst = re.finditer(p, s)
for w in rst:
    print(w, '\t', w.group(), '\t', w.group(1), '\t', w.group(2))
```

    <re.Match object; span=(0, 12), match='123ABCtarget'> 	 123ABCtarget 	 123ABC
    <re.Match object; span=(21, 33), match='targetDEF456'> 	 targetDEF456 	  	 DEF456
