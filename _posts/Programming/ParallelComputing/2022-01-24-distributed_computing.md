---
title: Distributed computing in separate networks
tags: ParallelComputing
---

<!--more-->

일반적으로 Cluster는 AWS, GCP 등을 통해 하나의 network 안에 있는 node들을 구성하는 방법을 주로 사용하는 것 같다. \
그러나 현재 분리된 network에 있는 여러 node들 안에 있는 container들을 사용하여 병렬 및 분산 처리를 해야하는 상황이 되었다.

처음엔 사실 그리 드문 상황은 아닌 것 같고 `dask.distributed`를 사용하면 무난하게 되지 않을까 싶었는데.. \
거의 2주간 자료탐색을 한 결과 다른 network에 있는 node들을 하나의 cluster로 묶는 작업에 대한 이야기를 찾기가 정말 힘들었다. 아마 cluster는 하나의 network 안에서만 주로 사용하는 듯?

[https://stackoverflow.com/questions/70766735/how-to-configure-two-servers-with-different-ip-in-different-networks-into-one-cl](https://stackoverflow.com/questions/70766735/how-to-configure-two-servers-with-different-ip-in-different-networks-into-one-cl) \
[https://github.com/dask/dask/discussions/8594](https://github.com/dask/dask/discussions/8594) \
[https://www.youtube.com/watch?v=q_aTbb7XeL4](https://www.youtube.com/watch?v=q_aTbb7XeL4)

여기저기 질문도 올려봤는데 사람들이 관심이 없는건지 모르는건지 대답이 1도 없다. \
그래도 어찌어찌 간단하게 구조를 정리하여 [repository](https://github.com/alchemine/distributed_computing)를 만들었다.
