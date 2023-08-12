---
title: Remove Duplicates
tags: RegularExpression
---

<!--more-->

연속된 문자를 하나의 문자로 간단히 대체할 수 있다.

```python
import re

input_string  = 'eeddee'
output_string = re.sub(r'([a-z])\1+', r'\1', input_string)

assert output_string == 'ede'
```

1. `\1` \
**역참조(괄호로 묶인 그룹을 다시 사용)**를 사용
