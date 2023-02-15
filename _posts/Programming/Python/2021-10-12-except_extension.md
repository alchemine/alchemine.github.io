---
title: Except extension
tags: Python
---

{% highlight python linenos %}
from pathlib import Path

path = "/root/dir/file.csv"
name = Path(path).stem  # 'file'

{% endhighlight %}
