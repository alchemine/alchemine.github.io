---
title: Speed up Windows shortcut
tags: Programming_Etc
---

<!--more-->

[Windows 11 File Explorer slow to respond to keyboard commands](https://answers.microsoft.com/en-us/windows/forum/all/windows-11-file-explorer-slow-to-respond-to/f1ea9e48-d91e-4c06-b758-181568f17400) 참고

---

SSH 접속하거나 메모장을 킬 때 `Ctrl + Alt + T`, `Ctrl + Alt + N` 이런 식으로 shortcut을 지정해놓는데 반응이 꽤나 느린 경우가 있다. \
이런 경우, file explorer cache를 지워주면 반응속도가 빨라진다.

1. `Windows + R`
2. `C:\Users\%username%\AppData\Roaming\Microsoft\Windows\Recent\AutomaticDestinations` 이동
3. 내부 파일(cache) 제거

---

그러나 재부팅하면 다시 반응속도가 느려져 있다. 더 근본적인 해결 방법이 필요해 보인다.
