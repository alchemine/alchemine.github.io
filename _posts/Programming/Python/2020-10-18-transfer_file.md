---
title: File transfer using SCP
tags: Python
---

<!--more-->

Ubuntu에서 파일을 전송하기 위해 `scp` 명령어를 사용할 수 있습니다.  
다음은 `SENDER`가 `RECEIVER`에게 directory를 전송하는 코드입니다.  


```py
### Package
from socket import gethostbyname, gethostname
from os import system


### Info
RECEIVER_ID        = "..."

SENDER_IP          = "..."
RECEIVER_IP        = "..."

RECEIVER_PORT      = "..."

SENDER_DIRECTORY   = "..."
RECEIVER_DIRECTORY = "..."


### Command
CMD_SCP = f"scp -P {RECEIVER_PORT} -r {SENDER_DIRECTORY} {RECEIVER_ID}@{RECEIVER_IP}:{RECEIVER_DIRECTORY}"


### Transfer
if gethostbyname(gethostname()) == SENDER_IP:
    system(CMD_SCP)
```
