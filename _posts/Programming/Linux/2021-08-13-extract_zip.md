---
title: Extract large zip file
tags: Linux
---

```
$ apt-get update -y
$ apt-get install -y dtrx
$ dtrx data.zip
```

<!--more-->

일반적으로 linux에서 zip file을 해제할 때 `unzip`, `7z`, `jar` 등의 프로그램을 사용할 수 있지만 상당히 큰(10GB 이상) zip file을 해제하는 것은 일반적인 방법으론 되지 않는 것 같다.  

여러가지 방법들을 실행해본 결과, `dtrx`를 통해 큰 압축파일을 해제할 수 있었다.  

```
$ apt-get update -y
$ apt-get install -y dtrx
$ dtrx data.zip
```
