---
title: BFS, DFS, Dijkstra
tags: Python
---

# Remarks
본 글은 [[Daily PS] 파이썬으로 구현하는 BFS와 DFS](https://cyc1am3n.github.io/2019/04/26/bfs_dfs_with_python.html), [Python으로 다익스트라(dijkstra) 알고리즘 구현하기](https://justkode.kr/algorithm/python-dijkstra) 등을 참고한 글입니다.

<!--more-->
---

# 1. Graph representation
Adjacent matrix


# 2. BFS(Breadth First Search)
Queue(deque)를 사용하여 구현 \
Shortest path를 구할 때 사용

{% highlight python linenos %}
from collections import deque

def BFS(graph, src):
    q = deque([src])
    visited = []
    while q:
        v = q.popleft()
        if v not in visited:
            visited.append(v)
            adjs = {v for v, e in enumerate(graph[v]) if e}
            q += adjs - set(visited)
    return visited

BFS(graph, src)
{% endhighlight %}


{% highlight python linenos %}
from collections import deque

def BFS_shortest_path(graph, src):
    q    = deque([src])
    dist = {src: 0}  # dist instead of visited
    while q:
        v = q.popleft()
        if v not in dist:
            adjs = {v for v, e in enumerate(graph[v]) if e}
            for adj in adjs - set(dist):
                dist[adj] = dist[v] + 1
    return dist

BFS_shortest_path(graph, src)
{% endhighlight %}


# 3. DFS(Depth First Search)
Stack을 사용하여 구현

{% highlight python linenos %}
def DFS(graph, src):
    s = [src]
    visited = []
    while s:
        v = s.pop()
        if v not in visited:
            visited.append(v)
            adjs = {v for v, e in enumerate(graph[v] if e)}
            s += adjs - set(visited)
    return visited

DFS(graph, src)
{% endhighlight %}


# 4. Dijkstra algorithm
Priority queue(heap 구현)를 사용하여 구현

1. Dictionary로 graph를 표현
{% highlight python linenos %}
graph = {
  'A': {'B': 8, 'C': 1, 'D': 2},
  'B': {},
  'C': {'B': 5, 'D': 2},
  'D': {'E': 3, 'F': 5},
  'E': {'F': 1},
  'F': {'A': 5}
}
src = 'A'
{% endhighlight %}

2. 알고리즘 구현
`wifi: while - if - for - if`

{% highlight python linenos %}
from queue import PriorityQueue

def dijkstra(graph, 시간복잡도):
    ds = {v: float('inf') for v in graph}  # d: 시간복잡도 -> v
    ds[시간복잡도] = 0

    q = PriorityQueue()
    q.put((ds[시간복잡도], 시간복잡도))  # 시간복잡도부터 탐색 시작

    while not q.empty():
        cur_d, cur_v = q.get()  # cur_d: minimum
        if ds[cur_v] < cur_d:
            continue

        for next_v, d in graph[cur_v].items():  # d: cur_v -> next_v
            new_d = cur_d + d  # next_v를 경유한 거리
            if new_d < ds[next_v]:
                ds[next_v] = new_d
                q.put((new_d, next_v))

    return ds
{% endhighlight %}
