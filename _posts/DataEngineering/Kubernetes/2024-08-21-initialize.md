---
title: Initialize Kubernetes
tags: Kubernetes
---

<!--more-->

GCP에 있는 GKE 서비스를 통해 Kubernetes를 접하고 data pipeline을 배포해볼 수 있는 좋은 기회를 얻었다. \
이미 프로젝트와 환경이 갖춰져 있는 상태라 날먹이긴 하지만 그래도 Ubuntu에서 GCP 접속 및 Kubernetes 관련 utility 프로그램을 설치하는 과정을 찬찬히 기록해보고자 한다.


### 1. Google Cloud CLI 설치 및 설정
1. `gcloud` 설치 \
CLI에서 GCP를 다루기 위해 Google cloud CLI를 설치한다.
    - [Google Cloud CLI 설치](https://cloud.google.com/sdk/docs/install-sdk?hl=ko)

2. 계정 인증
    ```bash
    gcloud auth login
    ```

3. 계정 및 작업 프로젝트 설정
    ```bash
    gcloud config set account [ACCOUNT]
    gcloud config set project [PROJECT_ID]
    ```

4. `kubectl`, `gke-gcloud-auth-plugin` 설치
    ```bash
    gcloud components install kubectl
    gcloud components install gke-gcloud-auth-plugin
    ```
    - https://cloud.google.com/kubernetes-engine/docs/how-to/cluster-access-for-kubectl?hl=ko#install_plugin

5. Cluster 인증
    ```bash
    gcloud container clusters get-credentials [CLUSTER_NAME] --region [REGION]
    ```

### 2. Utility 설치
1. k9s
    - https://k9scli.io/
2. OpenLens
    - https://github.com/MuhammedKalkan/OpenLens

### 3. 행복코딩