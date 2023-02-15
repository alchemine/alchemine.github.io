---
title: Multikey dictionary
tags: Python
---

# Remarks
`pandas.DataFrame`에 관한 자세한 설명은 [https://data-make.tistory.com/126](https://data-make.tistory.com/126) 을 참고

---

<!--more-->

기본적인 `dict` 자료형은 multikey를 지원하지 않는다.  
`tuple`을 key로 사용하는 것이 가장 직관적이나 각각의 key를 분리하기 어렵기 때문에 실용적이지 못하다.  
대신, `defaultdict`를 사용하면 multikey를 지원하는 dictionary를 그럭저럭 쓸 수 있을 정도로 흉내낼 수 있다.(sparse matrix, tree)  


{% highlight python linenos %}
from collections import defaultdict

Tree = lambda: defaultdict(Tree)
scores = Tree()
scores['1학년']['1반']['10번'] = 100
scores['2학년']['3반']['5번']  = 50
scores['3학년']                = 10  # multikey is not forced
{% endhighlight %}

혹은 [multi_key_dict](https://pypi.org/project/multi_key_dict/) package를 사용하는 것도 좋을 것 같다.


저장할 값들이 sparse 하지 않은 scalar matrix라면 가장 좋은 방법은 `pandas.DataFrame`을 사용하는 것이 베스트다.

{% highlight python linenos %}
import pandas as pd

data  = np.arange(16).reshape(4, 4)
index = [['1학년', '1학년', '2학년', '2학년'],
         ['1반', '2반', '1반', '2반']]
columns = [['남', '남', '여', '여'],
           ['50점 이상', '50점 미만', '50점 이상', '50점 미만']]

df = pd.DataFrame(data, index=index, columns=columns)
{% endhighlight %}


    	        남	                        여
                    50점 이상	50점 미만	50점 이상	50점 미만
    1학년	1반	0	       1	        2	        3
            2반	4	       5	        6          	7
    2학년	1반	8	       9	        10	        11
            2반	12	       13	        14	        15


{% highlight python linenos %}
### level0
df.loc['1학년']
df['남']
df.xs('1학년', axis=0, level=0)
df.xs('남', axis=1, level=0)

### level1
df.xs('1반', axis=0, level=1)
df.xs('50점 이상', axis=1, level=1)

### Join
df.loc['1학년', '1반']
df['남', '50점 이상']

{% endhighlight %}
