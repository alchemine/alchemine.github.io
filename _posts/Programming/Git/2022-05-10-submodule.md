---
title: Git Submodule
tags: Git
aside:
  toc: true
---

# Remarks
본 글은 [https://git-scm.com/book/ko/v2/Git-%EB%8F%84%EA%B5%AC-%EC%84%9C%EB%B8%8C%EB%AA%A8%EB%93%88](https://git-scm.com/book/ko/v2/Git-%EB%8F%84%EA%B5%AC-%EC%84%9C%EB%B8%8C%EB%AA%A8%EB%93%88)을 참고하여 작성되었습니다.

<!--more-->
---

Repository 안에 다른 repository를 넣고 version 관리를 따로 하고 싶은 경우, submodule 기능을 사용할 수 있다. \
이중으로 관리가 복잡해지기 때문에 적절한 상황에 적절하게 사용하도록 하자.


# 0. Summary
```
$ git config alias.supdate 'submodule update --remote --merge'
$ git config alias.spush 'push --recurse-submodules=on-demand'

$ cd submodule     # sub   module
$ git add, commit  # sub   module

$ cd ..            # super module
$ git supdate      # super module
$ git add, commit  # super module
$ git spush        # super module
```


# 1. Submodule 추가
```
$ git submodule add https://github.com/chaconinc/DbConnector
$ git commit -am 'added DBConnector module'
$ git push origin main
```


# 2. Submodule을 포함하는 프로젝트 clone
```
$ git clone --recurse-submodules https://github.com/chaconinc/MainProject
```


# 3. Submodule 관리
Submodule 내부에서 `add`, `commit`, `push` 등을 사용하는 방식도 사용할 수 있으나, \
상위 module과의 호환성 유지를 위해 다음의 명령어들을 사용하는 것이 좋다.

## 3.1 Submodule update
다음과 같이 **모든** submodule을 업데이트할 수 있다.

```
$ git submodule update --remote --merge
```


## 3.2 Submodule push
상위 directory로 나와 로컬 변경사항(submodule에서 `add`, `commit`된 내용)을 업데이트한 다음, \
Upstream repo로 push한다.

```
$ git submodule update --remote --rebase
$ git push --recurse-submodules=on-demand
```


# 4. Alias 생성
자주 사용하는 명령어들을 alias로 만들어 놓으면 편하다.

```
$ git config alias.sdiff '!'"git diff && git submodule foreach 'git diff'"
$ git config alias.supdate 'submodule update --remote --merge'
$ git config alias.spush 'push --recurse-submodules=on-demand'
$ git config alias.srebase 'submodule update --remote --rebase'
```
