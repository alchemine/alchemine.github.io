---
title: Activate Virtualenv in Dockerfile
tags: Docker
---

<!--more-->

Dockerfile 내에서 가상환경을 생성하고 가상환경을 활성화시킨 다음 무언가를 하기 위해선 약간의 트릭(?)이 필요하다.

`base` 라는 이름의 pyenv virtualenv를 생성하고, 그 안에 패키지를 설치하는 Dockerfile 예제를 살펴보자.

```Dockerfile
# syntax=docker/dockerfile:1
FROM nvidia/cuda:11.8.0-cudnn8-devel-ubuntu22.04

# change shell
SHELL ["/bin/bash", "-ic"]

# install pyenv, virtualenv
...

# create environment: base
RUN pyenv virtualenv 3.8.16 base && \
    pyenv activate base && \
    pip install torch torchvision torchaudio --index-url https://download.pytorch.org/whl/cu118 && \
    . /opt/docker/context/package/install_jupyter.sh

# set entrypoint, cmd
...
```

여기 2가지 포인트가 있다.

1. **기본 shell을 변경해야한다.** \
초기 shell은 `sh` 로 설정되어 있기 때문에, `RUN` 이후의 명령어들은 모두 `sh ...` 와 같은 명령어로 실행된다. \
이를 `/bin/bash -ic` 로 변경하면 `.bashrc`의 설정들을 사용할 수 있다.(`PYENV_PATH` 등) \
그리고 각각의 `RUN` 명령어들을 하나로 이어(`&&`) 중간에 shell이 종료되지 않고 순차적으로 실행될 수 있도록 해야한다.

2. **Shell script를 실행할 때는 `.`(comma)를 붙여준다.** \
Shell script를 실행할 때 앞에 있는 `.`는 `source`와 같은 의미를 가진다. \
즉, `. install.sh` 와 `source install.sh` 는 동일한 작업을 수행하며, 해당 script를 현재 shell에 `source`하는 것을 의미한다. \
따라서, 현재 activate한 가상환경이 유지된 상태로 script의 내용들을 실행할 수 있다.

여기선 `pyenv`를 사용하여 가상환경을 만들었지만, `anaconda`나 다른 툴들도 마찬가지로 동일한 방식으로 `Dockerfile`에서 가상환경을 사용할 수 있다.