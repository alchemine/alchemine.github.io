---
title: Activate GPU in docker-compose
tags: Docker
---

<!--more-->

`deploy.resources.reservations.device.device_ids`에 사용할 GPU id를 입력하면 container 내부에서 GPU를 사용할 수 있다.

```docker-compose
version: "3.8"

services:
  compute:
    build:
      context: .
    hostname: "dev"
    ports:
      - 10022:22
      - 8501:8501
      - 8888:8888
    volumes:
      - .:/opt/project
    environment:
      - PATH=/root/.local/bin/poetry:$PATH
    working_dir: /opt/project
    command: poetry run jupyter notebook
    restart: always
    privileged: true
    ipc: host
    tty: true
    deploy:
      resources:
        reservations:
          devices:
            - driver: nvidia
              device_ids: ['0']
              capabilities: [gpu]
```
