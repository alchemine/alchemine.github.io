---
title: Dev Container
tags: Python
---

<!--more-->

일관성 있는 개발환경을 구성하기 위해 `docker`, `pip`, `poetry`, `venv` 등 다양한 패키지 매니저들과 devops 툴들이 사용되고 있는데, 이들을 사용하여 container를 만들 수 있는 `dev container`를 소개해보고자 한다.

# Dev container
Dev container는 `Visual Studio Code`(이하 `VSCode`) 혹은 `JetBrains PyCharm`(이하 `PyCharm`)과 같은 IDE에서 사용할 수 있는 extension(plugin)으로 모든 기능들이 준비되어 있는 개발 환경을 container로 만들어 주는 역할을 한다. \
하는 역할은 일반적인 docker와 다를 바 없지만, IDE가 제공하는 다양한 기능들(theme, UI 등)을 container 내부에서 local(host)와 동일하게 사용할 수 있다는 점이 포인트이다.


# Usage
`VSCode`를 기준으로 설명하지만 `PyCharm`이나 다른 IDE에서도 대동소이한 방식으로 dev container 기능을 사용할 수 있다.

## 1. `dev containers` extension 설치
![Alt text](/images/Programming/Python/2024-02-05-dev_container/image.png)

## 2. Configuration 추가
![Alt text](/images/Programming/Python/2024-02-05-dev_container/image-1.png)

## 3. 설정에 맞춰 선택
![Alt text](/images/Programming/Python/2024-02-05-dev_container/image-2.png)
- 주로 `Dockerfile`, `docker-compose` 을 사용하여 기존 docker 환경을 사용한다.

## 4. 추가 기능 설치
![Alt text](/images/Programming/Python/2024-02-05-dev_container/image-3.png)
- `SSH`, `vim` 등 일반적으로 사용되는 기능들을 선택하여 container에 설치할 수 있다.

## 5. `devcontainer.json` 확인
![Alt text](/images/Programming/Python/2024-02-05-dev_container/image-4.png)
- 환경변수를 추가하거나, working directory의 위치를 변경하는 등 여러가지 설정이 가능하다.

## 6. Container 생성
![Alt text](/images/Programming/Python/2024-02-05-dev_container/image-5.png)


# `devcontainer.json` 설정
## 1. 환경변수
### 1.1 직접 추가
`devcontainer.json`에 다음과 같이 `containerEnv` 혹은 `remoteEnv`를 추가할 수 있다.

```
"containerEnv": {
    "MY_CONTAINER_VAR": "some-value-here",
    "MY_CONTAINER_VAR2": "${localEnv:SOME_LOCAL_VAR}"
},
"remoteEnv": {
    "PATH": "${containerEnv:PATH}:/some/other/path",
    "MY_REMOTE_VARIABLE": "some-other-value-here",
    "MY_REMOTE_VARIABLE2": "${localEnv:SOME_LOCAL_VAR}"
}
```

## 1.2 env file 사용
### 1.2.1 env file 생성
`.devcontainer/devcontainer.env` 를 env file로 사용할 수 있다.

```
OPENAI_API_KEY="..."
```

### 1.2.2 env file 적용
#### 1.2.2.1 Dockerfile or image
`devcontainer.json`에 다음과 같이 `runArgs`를 추가한다.
```
"runArgs": ["--env-file",".devcontainer/devcontainer.env"]
```

#### 1.2.2.2 Docker Compose
`.devcontainer/docker-compose.yml`에 적절한 service에 `env_file`을 추가한다.

```yml
version: '3.8'
services:
  compute:
    ...    
    env_file: devcontainer.env
```

## 2. `requirements.txt` 사용
다음과 같이 후처리 과정에서 python package를 추가로 설치할 수 있다.

```json
{
  ...
  
  "postCreateCommand": "pip install -r requirements.txt"
}
```

## 3. Docker build 관련
특정 위치에서 dev container 환경들을 일괄관리하는 방식도 좋다.
```json
{
  "name": "llm-app",
  "build": {
    "context": "${localEnv:CDE_PATH}/envs/docker/llm-app",
    "dockerfile": "${localEnv:CDE_PATH}/envs/docker/llm-app/Dockerfile"
  },

  ...
}

```
