---
title: Rename OneDrive Folder
tags: Etc
---

<!--more-->

기본적으로 OneDrive 동기화 폴더의 이름은 `Onedrive - username` 과 같은 형식으로 되어있다. \
이름에 space가 포함되어 있을뿐만 아니라 `username`은 한글로 되어 있는 경우가 많아 경로를 잡을 때 불편한 경우가 많은데 이 폴더명을 바꿀 수 있다.


1. `OneDrive` 종료
2. `OneDrive` 동기화 폴더명 변경 \
혹시 사용중인 폴더라는 메세지가 뜨면서 폴더명 변경이 안 된다면, `시작 앱`에서 `OneDrive`를 `사용 안 함`으로 변경하고 재부팅한 다음 시도해보자.
3. `OneDrive` 설정에서 동기화 폴더명 변경
    1. 레지스트리 편집기 실행 \
    `Ctrl+R` → `regedit`
    2. `컴퓨터\HKEY_CURRENT_USER\Software\Microsoft\OneDrive\Accounts`에서 변경하고 싶은 계정을 선택 \
    `UserFolder`를 확인하면 알 수 있는데, 나는 `Business2`로 설정되어 있었다.
    3. `%LOCALAPPDATA%\Microsoft\OneDrive\settings` 에서 계정 폴더로 들어가기
    4. `34be6bb5-0791-47b9-822f-4edd805dade5.ini` 와 같은 설정 파일 열기 \
    위와 같은 `*.ini` 파일을 열어 첫째줄 혹은 둘째줄에 있는 동기화 폴더의 이름을 수정하고 저장한다.
4. `OneDrive`를 실행한 후, 동기화 폴더를 확인
