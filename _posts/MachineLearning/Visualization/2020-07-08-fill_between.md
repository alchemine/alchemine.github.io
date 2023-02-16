---
title: Fill upper and lower than 0
tags: Visualization
---

<!--more-->

포인트는 `where` option을 통해 0와 비교하고, `interpolate` option으로 교차점 근처의 값을 안정화시켜주는 것



```Python
x = np.arange(0,10,0.1)
y1 = 4 - 2*x

# Plot the graph
plt.plot(x, y1)

# Filling between the graph and zero line
plt.plot(x, np.zeros(len(x)), 'k-', lw=2)
plt.fill_between(x, y1, where=(y1 >= 0), interpolate=True, alpha=0.3, color='b')
plt.fill_between(x, y1, where=(y1 < 0), interpolate=True, alpha=0.3, color='r')
plt.show()
```

![](/deprecated/images/2020-07-08-fille_between/1.png)

