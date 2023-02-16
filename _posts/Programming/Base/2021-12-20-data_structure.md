---
title: Data structure
tags: Programming_Base
---

# Remarks
본 글은 [https://github.com/JaeYeopHan/Interview_Question_for_Beginner/blob/master/DataStructure/README.md](https://github.com/JaeYeopHan/Interview_Question_for_Beginner/blob/master/DataStructure/README.md) 등을 정리한 내용입니다.

<!--more-->

---

# 1. Array vs Linked List

|  | **Array** | **Linked list** |
|:---:|:---:|:---:|
| 정의 | Index에 대응하는 데이터로 구성된 자료구조 | 데이터와 다음 노드를 가리키는 포인터를 가지는 노드들로 구성된 자료구조 |
| 특징 | 논리적 저장 순서 = 물리적 저장 순서 | 논리적 저장 순서 ≠ 물리적 저장 순서 |
|  | 임의의 원소에 직접 접근가능 (random access) | 임의의 원소에 접근하기 위해 연속적인 순회가 필요 (sequential access) |
|Access|$O(1)$|$O(n)$|
|Insertion|$O(n)$|$O(n)$|
|Deletion|$O(n)$|$O(n)$|

## 1.1 Array doubling
Array가 꽉 찼을 때 insertion 연산이 수행되는 경우, array의 크기를 2배로 늘린다.

1. $k$: 크기를 늘리기 전 array(`prevArray`)의 크기
2. $k+c$: 크기를 늘린 후 array(`postArray`)의 크기
3. $t$: `prevArray[i]`를 `postArray[i]`로 이동시키는데 소요되는 시간(transferring cost)
4. Array의 크기가 $n$이 될 때까지 크기를 늘리는데 소요되는 transferring cost $T$는 다음과 같다. \
$T(n)=\sum_i^{\lfloor log_2(n) \rfloor} 2^{i-1}=O(n)$
{:.info}

## 1.2 Implementation
[Array.cpp](https://github.com/alchemine/alchemine.github.io/blob/master/_posts/Prog/CS/1_Array_LinkedList/Array.cpp), [LinkedList.cpp](https://github.com/alchemine/alchemine.github.io/blob/master/_posts/Prog/CS/1_Array_LinkedList/LinkedList.cpp)


# 2. Stack vs Queue

|  | **Stack** | **Queue** |
|:---:|:---:|:---:|
| 정의 | Last In Last Out(LILO) 선형구조를 갖는 자료구조 | Last In First Out(LIFO) 선형구조를 갖는 자료구조 |

1. **Stack을 사용한 미로찾기** \
[DFS 알고리즘](https://alchemine.github.io/2021/09/28/bfs_dfs_dijkstra.html#3-dfsdepth-first-search)
2. **Queue를 사용하여 Heap 자료구조 구현하기** \
??
3. **Stack 2개로 Queue 자료구조 구현** \
Stack1: 입력, Stack2: Stack1에 있는 값들을 입력으로 받은 후 출력
4. **Stack으로 괄호 유효성 체크 코드 구현하기** \
`(`: `push`, `)`: `pop`

## 2.1 Implementation
[Stack.cpp](https://github.com/alchemine/alchemine.github.io/blob/master/_posts/Prog/CS/2_Stack_Queue/Stack.cpp), [Queue.cpp](https://github.com/alchemine/alchemine.github.io/blob/master/_posts/Prog/CS/2_Stack_Queue/Queue.cpp)

# 3. Tree
1. **정의**: 계층적 관계를 표현하는 비선형 자료구조
2. **용어**
    1. **Node**: 트리를 구성하는 각각의 요소
    2. **Edge**: Node와 node를 연결하는 선
    3. **Root node**: 트리 구조의 최상위에 위치한 node
    4. **Terminal(external, leaf) node**: 하위에 다른 노드가 연결되어 있지 않은 node
    5. **Internal(branch) node**: Terminal node를 제외한 모든 node
    6. **Parent(부모)**: Edge로 연결된 두 node 중 상위 계층의 node
    7. **Child(자식)**: Edge로 연결된 두 node 중 하위 계층의 node
    8. **Sibling(형제)**: 부모가 같은 node들
    9. **Node의 degree(차수)**: 해당 node의 자식의 수
    10. **Node의 depth(깊이)**: Root node에서 해당 node까지의 경로의 길이
    11. **Node의 level(레벨)**: Node의 depth + 1
    12. **Node의 height(높이)**: 해당 node와 terminal node 간의 경로의 최대 길이
    13. **Node의 size(크기)**: 자기 자신 및 모든 자손 node의 수
    14. **Tree의 depth, level, size**: Tree에 포함된 모든 node들에 대한 depth, level, size의 최댓값

## 3.1 Binary Tree
1. **정의**: 각각의 node가 최대 2개의 자식 node를 가지는 tree 자료구조
2. **Complete Binary Tree: Array 구현** \
    ```
    arr[1]: Root node

    For i ≥ 1,
    arr[i]: Parent of left child(2i), right child(2i+1)
    ```

|  | **Perfect Binary Tree(포화 이진 트리)** | **Complete Binary Tree(완전 이진 트리)** | **Full Binary Tree(정 이진 트리)** |
|:---:|:---:|:---:|:---:|
| 정의 | 모든 internal node가 2개의 자식 노드를 가지며 모든 leaf node가 동일한 깊이를 가지는 tree 자료구조 | 마지막 level을 제외한 모든 level이 완전히 채워져 있으며, 마지막 level의 leaf node들은 가능한 한 가장 왼쪽에 있는 tree 자료구조 | 모든 node가 0개 혹은 2개의 자식 node만을 갖는 tree 자료구조 |

### 3.1.1 Implementation
[BinaryTree.cpp](https://github.com/alchemine/alchemine.github.io/blob/master/_posts/Prog/CS/3_Tree/BinaryTree.cpp)


## 3.2 Binary Search Tree(BST)
1. **정의**: 다음의 정의를 만족시키는 tree 자료구조
    1. Node에 저장된 key는 유일
    2. key(right child) ≥ key(parent) ≥ key(left child)
    3. Left, right sub tree도 BST
2. **Rebalancing** \
$n$개의 값으로 구성된 BST의 탐색 연산의 시간복잡도는 $O(h)$($h$: tree의 높이)이다. \
$h$가 $log n$이 되도록 균형을 잡는 작업을 **rebalancing**이라 한다.

## 3.3 Binary Heap
1. **정의**: **Heap property**를 만족시키는 Complete Binary Tree이다.
    1. **Heap property** \
    Max heap: 모든 node에 대하여, key(parent) ≥ key(child) \
    Min heap: 모든 node에 대하여, key(parent) ≤ key(child)
2. **Rebalancing: heapify** \
Heap에 값을 추가, 삭제한 후 Tree의 높이를 $\lfloor log n \rfloor$으로 유지(Complete Binary Tree)하고 heap property를 만족시키기 위해 **heapify** 연산을 수행한다.

### 3.3.1 Priority Queue
1. **정의**: 우선순위에 따라 출력되는 순서가 결정되는 자료구조
2. **일반적인 구현** \
선형구조를 가지는 queue와 달리 heap을 통해 구현

#### 3.3.1.1 Implementation
[BinaryHeap.cpp](https://github.com/alchemine/alchemine.github.io/blob/master/_posts/Prog/CS/3_Tree/BinaryHeap.cpp)


## 3.3 Red-Black Tree
1. **정의**: 다음의 조건을 만족시키는 BST 자료구조
    1. (Color property) 각 node는 `red`, `black`이라는 색깔을 갖는다.
    2. (Root property) Root node: `black`
    3. (External property) Leaf node: `black`
    4. (Interal property) `red` node의 자식: `black`
    5. (Depth property) 각 node에서 leaf node까지의 경로들은 모두 같은 개수의 `black` node를 포함(`black-height`, `black-depth`)

2. **특징**
    1. Search, Insertion, Deletion: $O(log n)$
    2. 모든 root node → leaf node 경로들 중 **최대길이/최소길이 ≤ 2** (balanced)
    3. Child가 없는 node들의 child pointer에 NIL을 저장(NIL들을 leaf node로 간주)


# 4. Hash Table
1. **정의**: key를 value에 mapping하는 연관 배열(associative array, map, dictionary)을 구현하는 자료구조
2. **특징**
    1. Search, Insert, Delete: $O(1)$ (average case)
    2. Space complexity: $O(n)$
3. **Mapping algorithm**
    ```
    n: number of data

    1. A: Bucket array(with size N(capacity), n < N)
      A[key]: Bucket containing (key, value)

    2. hash(): Hash function
      hash: key → index(integer ∊ [0, N-1])

    3. Map (key, value)
      A[hash(key)] ← value
    ```
4. **Collision(Conflict)** \
`hash(key1) = hash(key2)`인 경우, **충돌(collision)**이 발생했다고 한다.

5. **Desired hash function**
    1. 충돌이 적게 발생
    2. 공간(bucket array)을 효율적으로 사용
    3. 계산이 빠르고 쉬움

## 4.1 Resolve Collision
### 4.1.1 Open addressing
1. 충돌 발생(`h=hash(key)`) 시, 다른 bucket에 entry(key, value)를 삽입하는 방식
2. Load factor(`n/N`): < 0.5 가 적절
    1. Linear probing: Probe `A[(h + i) % N]`
    2. Quadratic probing: Probe `A[(h + i^2) % N]`
    3. Double hashing probing: `A[(h + hash'(i)) % N]`

### 4.1.2 Separate Chaining
1. 각 bucket에 Linked list, Red-Black Tree 등의 참조를 저장하는 방식
2. 한 bucket에 할당된 entry의 개수가 6, 8개를 기준으로 적어지면 linked list, 많아지면 tree를 사용
3. Load factor(`n/N`): < 0.9 가 적절

### 4.1.3 Open addressing vs Separate Chaining
1. Bucket array의 밀도가 높아질수록 worst case 발생 빈도가 높아져 일반적으로 separate chaining의 성능이 더 좋음
2. Separate chanining 방식은 bucket array의 확장을 늦출 수 있음
3. 데이터 개수가 충분히 적다면 open addressing 방식이 cache 효율이 높아 성능이 좋음

## 4.2 Bucket array resizing
Load factor가 75%가 되면 bucket array를 2배로 늘린다.


# 5. Graph
1. **정의**: Vertex(정점)과 그들 간의 쌍으로 된 연결들(edge)의 집합
2. **Tree와의 관계** \
    1. Tree는 DAG(Directed Acyclic Graph)의 특별한 케이스
    2. Tree의 두 정점간의 경로는 1개
    3. Tree는 loop가 없음
    4. 모든 자식 node는 하나의 부모 node를 가짐
3. **용어**
    1. **Vertex의 degree(차수)**: Vertex와 연결된 edge의 개수
    2. **Indegree**: Vertex로 들어오는 edge의 개수
    3. **Outdegree**: Vertex로 나가는 edge의 개수
    4. **Adjacent(인접)**: Vertex가 `u`, `v`인 edge가 존재하면 `u`와 `v`는 adjacent
    5. **Incident(연결)**: Vertex가 `u`에 연결된 edge 와 `u`는 incident
    6. **Simple graph**: parallel edge, self-loop가 없는 graph
4. **Vertex와 Edge**
    1. $n = \mid V \mid, m = \mid E \mid$
    1. $\sum_i degree(V_i) = 2m$
    2. $m = O(n^2)$

## 5.1 Graph 구현

| | Adjacent matrix | Adjacent list |
|:--:|:--:|:--:|
| 자료구조 | $M: (n \times n)$ 2d array | $L: (n)$ Linked list를 원소로 하는 array |
| 구성 | $M[i,j]$: $V_i, V_j$와 연결된 edge의 개수 | $L[i]$: $V_i$와 인접한 vertex들의 linked list |
| 두 vertex가 인접한지 확인 | $O(1)$ | $O(n)$ |
| Space complexity | $O(n^2)$ | $O(n+m)$ |
| 사용에 적절한 상황 | Dense graph | Sparse graph |

## 5.2 Graph traversal

|   | Depth First Search(DFS) | Breadth First Search(BFS) |
|:--:|:--:|:--:|
| 사용되는 자료구조  | Stack | Queue |
| Time complexity | $O(n+m)$  | $O(n+m)$ |
| 활용 | 미로 찾기 | 최단 경로 |

## 5.2.1 Implementation
[BFS, DFS](https://alchemine.github.io/2021/09/28/bfs_dfs_dijkstra.html)
