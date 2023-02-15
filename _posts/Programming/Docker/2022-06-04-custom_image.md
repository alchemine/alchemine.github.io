---
title: Prepared CUDA based Machine Learning Project Image
tags: Docker
---

[https://hub.docker.com/repository/docker/djyoon0223/base](https://hub.docker.com/repository/docker/djyoon0223/base)

```
$ docker pull djyoon0223/base:basic
$ docker pull djyoon0223/base:full
```

<!--more-->
---

매번 개발환경을 준비하느라 많은 시간이 걸렸는데 주로 사용하는 package들로 docker image로 만들어보았다.

- **Base image**: `nvidia/cuda:11.2.0-cudnn8-devel-ubuntu20.04`

1. `djyoon0223/base:basic` \
`nvidia/cuda:11.2.0-cudnn8-devel-ubuntu20.04` + `miniconda` + `jupyter`
2. `djyoon0223/base:full` \
`nvidia/cuda:11.2.0-cudnn8-devel-ubuntu20.04` + `miniconda` + `jupyter` + `rapids(cudf, cuml)` + `pycaret` + `tensorflow` + `torch` + `opencv`

자세한 내용은 [github](https://github.com/alchemine/base_env) 혹은 [dockerhub](https://hub.docker.com/repository/docker/djyoon0223/base)를 참조
