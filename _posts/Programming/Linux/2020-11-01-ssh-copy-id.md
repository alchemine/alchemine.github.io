---
title: ssh-copy-id
tags: Linux
---

<!--more-->

`ssh`로 서버에 접속할 때 인증되지 않은 client인 경우 매번 비밀번호를 물어봅니다.  
Server가 인증된 client를 구별하기 위해 `.ssh/authorized_keys` 안에 있는 public key(client의 `.ssh/id_rsa.pub`)들을 사용합니다.  

Client 단에서 public key를 손쉽게 server로 전송시켜주는 명령어가 있으니, 바로 `ssh-copy-id` 입니다.

```
$ ssh-copy-id USER@IP [-p PORT]
```