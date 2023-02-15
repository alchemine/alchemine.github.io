---
title: Google drive download with wget
tags: Linux
---

# Remarks
본 글은 [Download Google Drive Files using wget](https://medium.com/@acpanjan/download-google-drive-files-using-wget-3c2c025a8b99)의 내용을 정리한 글입니다.

<!--more-->

--- 

`public`으로 공개된 Google drive file에 할당된 `id`를 이용하여 file을 받아올 수 있다.  

1. 32MB 이하  
        
       wget --no-check-certificate 'https://docs.google.com/uc?export=download&id=파일ID' -O 파일이름

2. 32MB 이상

       wget --load-cookies /tmp/cookies.txt "https://docs.google.com/uc?export=download&confirm=$(wget --quiet --save-cookies /tmp/cookies.txt --keep-session-cookies --no-check-certificate 'https://docs.google.com/uc?export=download&id=파일ID' -O- | sed -rn 's/.*confirm=([0-9A-Za-z_]+).*/\1\n/p')&id=파일ID" -O 파일이름 && rm -rf /tmp/cookies.txt
