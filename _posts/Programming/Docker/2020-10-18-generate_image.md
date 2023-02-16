---
title: Generate custom docker image (commit, push, pull)
tags: Docker
---

<!--more-->

초기 docker image로부터 나만의 image를 만들어 docker hub에 올리는 과정입니다.  
Server에서 container를 생성한다고 가정하겠습니다.


### 1. 초기 상태가 되는 docker image 받아오기
    $ docker pull rapidsai/rapidsai

[rapidsai](https://hub.docker.com/r/rapidsai/rapidsai/)  
[deepo](https://hub.docker.com/r/ufoym/deepo/)
등등

원하는 docker hub로부터 image를 받아옵니다.


### 2. Container를 생성
    $ docker run -itd \
    --name custom_container \
    --hostname server \
    --gpus all \
    --restart always \
    --ip 123.45.0.11 \
    -v ~/data:/data \
    -v ~/project:/project \
    -p 10022:22 \
    -p 15006:5006 \
    -p 18888:8888 \
    -p 18787:8787 \
    rapidsai/rapidsai

Container의 정보를 적고 생성합니다.  

#### - Options
1. **GPU 선택**

       --gpus '"device=1,2"'  // 특정 GPU만 사용 (nvidia-smi 에서의 순서와 동일)
       --gpus all             // 모든 GPU를 사용

2. **Volume**  
외부 directory와 container의 directory를 동기화


       --v OUT_DIR_PATH:CONTAINER_DIR_PATH

3. **Restart**  
Server가 켜졌을 때 container를 자동으로 `start` 하게 할 수 있음

       --restart always

4. **Port forwarding**  
외부의 port와 container 내부의 port를 동기화

       --p 10022:22  // 외부의 10022 port로 내부의 22 port 접속가능


### 3. Linux 기본설정
1. **`bash` 접속**
    
       $ docker exec -it custom_container /bin/bash
       
2. **`apt` upgrade**

       $ apt-get update && apt-get upgrade -y

3. **기타 package 설치**

       $ apt-get install -y wget vim git gcc build-essential net-tools iproute2 ufw

4. **ssh 설정**  
[Ubuntu ssh setting](https://alchemine.github.io/2019/10/10/ssh.html#gsc.tab=0) 참고

5. **`conda`, `pip` update**  
[Python package management](https://alchemine.github.io/2020/02/25/upgrade_pkg.html#gsc.tab=0) 참고


### 4. Commit
  
    $ docker login
    $ docker commit CONTAINER_ID DOCKER_ID/DOCKER_REPOSITORY:TAGNAME
    
Docker hub에 login 한 후, 형식에 맞추어 container를 commit 하여 image를 생성합니다.


### 5. Push

    $ docker push DOCKER_ID/DOCKER_REPOSITORY
    
생성한 docker image를 docker hub로 push 합니다.  
push된 image는 docker hub의 repository에서 확인할 수 있습니다.


### 6. Pull

    $ docker pull DOCKER_ID/DOCKER_REPOSITORY:TAGNAME
    
Docker hub에 저장된 image를 불러올 수 있습니다.


### Optional
Docker image를 받아온 다음,  
1. **Jupyter notebook 설정**
[Access remote jupyter-notebook](https://alchemine.github.io/2019/10/10/remote_jupyter#gsc.tab=0) 참고

2. **Rstudio-server 설정**
[R, IRkernel, RStudio installation in Ubuntu](https://alchemine.github.io/2019/10/18/install.html#gsc.tab=0) 참고
