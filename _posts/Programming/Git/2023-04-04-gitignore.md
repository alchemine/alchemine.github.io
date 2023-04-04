---
title: Apply .gitignore
tags: Git
---

<!--more-->

기존의 파일이나 디렉터리를 `.gitignore` 에 추가할 경우 cache를 지워주어야 정상적으로 작동한다.

```bash
$ git rm -r --cached .
$ git add .
```

참고로 vscode는 cache를 자동적으로 처리해주는 것 같다.
