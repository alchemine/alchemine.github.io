---
title: JetBrains dummy data 제거
tags: Programming_Etc
---

# Remarks
본 글은 [Is it safe to delete C:\Users\user\AppData\Local\JetBrains\IdeaIC2020.3 folder](https://intellij-support.jetbrains.com/hc/en-us/community/posts/360010670000-Is-it-safe-to-delete-C-Users-user-AppData-Local-JetBrains-IdeaIC2020-3-folder) 의 내용을 정리한 글입니다.

---
<!--more-->

[PyCharm](https://www.jetbrains.com/pycharm/) update를 할 때 system directory에 기존 버전의 파일들이 남아있는 경우가 있다.
그런 경우에는 해당 파일들이 현재 사용되고 있지 않다는 것을 확인하고 제거하는 것이 좋다.

- **현재 사용 버전** \
`PyCharm2021.3(C:\Users\{USERNAME}\AppData\Local\JetBrains\PyCharm2021.3)`
- **이전 사용 버전** \
`PyCharm2021.1(C:\Users\{USERNAME}\AppData\Local\JetBrains\PyCharm2021.1)` \
`PyCharm2021.2(C:\Users\{USERNAME}\AppData\Local\JetBrains\PyCharm2021.2)`


### 1. Pycharm에서 사용 중인 파일인지 확인
`Help → Show Log in Explorer`

![](/images/2022-01-07-remove_dummy/001.jpg)

이전 버전이 log 파일에서 사용되고 있지 않는 것을 확인

### 2. 미사용 확인 후 제거
- **디렉토리 제거** \
`PyCharm2021.1(C:\Users\{USERNAME}\AppData\Local\JetBrains\PyCharm2021.1)` \
`PyCharm2021.2(C:\Users\{USERNAME}\AppData\Local\JetBrains\PyCharm2021.2)`
