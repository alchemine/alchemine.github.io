---
title: Streamlit
tags: Visualization
---

# Streamlit: A faster way to build and share data apps
> Streamlit turns data scripts into shareable web apps in minutes. \
All in pure Python. No front‑end experience required.

- Official link: [https://streamlit.io/](https://streamlit.io/)

<!--more-->
---

# Streamit
복잡한 front-end 기술이 필요하지 않을 정도의 간단한 데이터 대시보드 어플리케이션을 만들 수 있는 python library


# 1. Three Simple Principles
## 1) Embrace Scripting
페이지를 동적으로 렌더링하기 때문에 **스크립트를 저장하기만 해도 변화가 적용됨**
- 다만, 메인 페이지에서 불러오는 **module 내부의 변화는 적용시켜주지 않음**

## 2) Weave in Interaction
간단히 다양한 종류의 widget(`slider`, `radio`, `date_input` 등)을 만들고 그 값을 변수로 받아올 수 있음

## 3) Deploy Instantly
Stremlit official site에서 github 연동을 통해 간단하히 애플리케이션 배포가 가능


# 2. Powerful Apps
이미 다양한 종류의 애플리케이션 예제들이 제공되고 있으니 적절한 템플릿을 골라서 시작하자

- App Gallery: [https://streamlit.io/gallery](https://streamlit.io/gallery)
- Streamlit Cheat Sheet: [https://cheat-sheet.streamlit.app/](https://cheat-sheet.streamlit.app/)


# 3. Features
## 1) Deployment with Docker-compose
- Reference: [https://github.com/alchemine/diabetes-prediction](https://github.com/alchemine/diabetes-prediction)

1. `Dockerfile`
    ```docker
    # syntax=docker/dockerfile:1
    FROM alchemine/base-cuda:11.8.0-cudnn8-runtime-ubuntu22.04

    # copy project directory
    COPY . /project
    WORKDIR /project

    # install python environment
    RUN poetry env use python3.9 && \
        poetry install --no-root
    ```
2. `docker-compose.yml`
    ```docker
    version: "3.8"

    services: 
    app:
        build:
            context: .
        hostname: "dev"
        ports:
            - 10022:22
            - 8501:8501
            - 8888:8888
        volumes:
            - .:/project
        environment:
            - PATH=/root/.local/bin/poetry:$PATH
        working_dir: /project
        command: poetry run streamlit run diabetes_prediction/app.py
        privileged: true
        ipc: host
        tty: true
    ```
