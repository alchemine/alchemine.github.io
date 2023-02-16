---
title: Container IP 변경하기
tags: Docker
---

<!--more-->

여러 개의 서버에서 container에 접근할 때 모두 동일한 IP를 가지고 있어서 구분하기 어려운 경우가 있습니다.(심지어 MAC 주소도) 이런 경우, 다음과 같은 방법을 통해 IP를 바꿔줄 수 있습니다.


### 1. Docker service 멈추기

    $ service docker stop

### 2. 변경할 IP 추가
`/etc/docker/daemon.json`에 `bip`를 key로 하는 item을 추가합니다.

    $ vi /etc/docker/daemon.json

    // daemon.json
    {
      "bip": "172.18.0.1/16",
      ...
    }


`/etc/default/docker`에도 변경한 IP를 추가합니다.

    $ vi /etc/default/docker

    // docker
    ...
    DOCKER_OPTS="--bip 172.18.0.1/16"

### 3. Docker service를 재가동

    $ service docker start


### 4. IP 확인

    $ hostname -i
