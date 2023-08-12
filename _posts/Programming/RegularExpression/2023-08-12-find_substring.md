---
title: Find Substring
tags: RegularExpression
---

<!--more-->

```python
import re

s = "123ABCtarget tar get targetDEF456 789GHI"
p = r"[^\s]*target[^\s]*"

rst = re.search(p, s)
print(rst, '\t', rst.group())
```

    <re.Match object; span=(0, 12), match='123ABCtarget'> 	 123ABCtarget



```python
s = "123ABCtarget tar get targetDEF456 789GHI"
p = r"[^\s]*target[^\s]*"

rst = re.findall(p, s)
print(rst)
```

    ['123ABCtarget', 'targetDEF456']



```python
s = "123ABCtarget tar get targetDEF456 789GHI"
p = r"[^\s]*target[^\s]*"

rst = re.finditer(p, s)
for w in rst:
    print(w, '\t', w.group())
```

    <re.Match object; span=(0, 12), match='123ABCtarget'> 	 123ABCtarget
    <re.Match object; span=(21, 33), match='targetDEF456'> 	 targetDEF456



```python
s = "123ABCtarget tar get targetDEF456 go al goalDEF789"
p = r"[^\s]*target|goal[^\s]*"

rst = re.findall(p, s)
print(rst)
```

    ['123ABCtarget', 'target', 'goalDEF789']