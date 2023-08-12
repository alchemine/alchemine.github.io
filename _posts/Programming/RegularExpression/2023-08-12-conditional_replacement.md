---
title: Conditional Replacement
tags: RegularExpression
---

<!--more-->


```python
import re

s = "A: 0.75, B: 0.5, C: 0.25, D: 0"

def float2percent(match):
    return f"{match.group(1)}{100*float(match.group(2))}%"

rst = re.sub(r"(\w: )([0-9.]*)", float2percent, s)
rst
```

    'A: 75.0%, B: 50.0%, C: 25.0%, D: 0.0%'



---

{% highlight python linenos %}
p = "\(?(\-?[\d]+)\)?\*\(?(\-?[\d]+)\)?"

s   = "100*200+300"
rst = re.search(p, s)
print("\ns:", s)
print("group():", rst.group())
print("group(1):", rst.group(1))
print("group(2):", rst.group(2))

s   = "100*(-200)-300"
rst = re.search(p, s)
print("\ns:", s)
print("group():", rst.group())
print("group(1):", rst.group(1))
print("group(2):", rst.group(2))

s   = "-100*(-200)/300"
rst = re.search(p, s)
print("\ns:", s)
print("group():", rst.group())
print("group(1):", rst.group(1))
print("group(2):", rst.group(2))

s   = "(-100)*(-200)%300"
rst = re.search(p, s)
print("\ns:", s)
print("group():", rst.group())
print("group(1):", rst.group(1))
print("group(2):", rst.group(2))
{% endhighlight %}


```
s: 100*200+300
group(): 100*200
group(1): 100
group(2): 200

s: 100*(-200)-300
group(): 100*(-200)
group(1): 100
group(2): -200

s: -100*(-200)/300
group(): -100*(-200)
group(1): -100
group(2): -200

s: (-100)*(-200)%300
group(): (-100)*(-200)
group(1): -100
group(2): -200
```
