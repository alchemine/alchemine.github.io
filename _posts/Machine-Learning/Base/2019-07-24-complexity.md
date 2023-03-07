---
title: Computational complexity of ML algorithms
tags: MachineLearning_Base
---

*sklearn* 등에서 구현된 machine learning algorithm들은 굉장히 최적화가 잘 되어 손으로 계산하는 naive한 복잡도보다 훨씬 더 빠르게 작동하도록 구현되어 있습니다.

예를 들어, 정규방정식의 복잡도는 $O(mn^2)$으로 알려져 있지만 실제론 $O(m^{0.72}n^{1.3})$ 정도의 복잡도까지 최적화되어있습니다.

자세한 내용은 [https://www.thekerneltrip.com/machine/learning/computational-complexity-learning-algorithms/](https://www.thekerneltrip.com/machine/learning/computational-complexity-learning-algorithms/)을 참조!
