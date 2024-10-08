---
title: VI Editor Shortcut
tags: Programming_Etc
---

<!--more-->

데이터를 분석하거나 디버깅할 때는 IDE가 상당히 편리하기 때문에 VI editor에서 코딩을 하지는 않는다. \
다만, 타자를 치면서 A-Z를 제외한 키들이나 마우스를 사용하는 경우 불편함을 많이 느끼던터라 결국 VIM plugin을 설치하게 되었다.

그래서 이번 글은 VIM에서 주로 사용하는 단축키들을 알아보고 익숙해지는 시간을 가지고자 한다. \
기본적으로 너무 많은 단축키들 때문에 VI editor의 진입장벽이 높지만 가장 기초적인 것부터 차근차근 알아가보면 점점 익숙해지지않을까.


# Change Mode
```
ESC : Edit mode → Command mode
```

# 1. Cursor Position
## 1.1 Character
```
h j k l : ← ↓ ↑ →
```

## 1.2 Word
```
b w : ← →
```

## 1.3 Line
정규표현식의 meta character가 여기서 따온 듯? 아니면 반대일지도..
```
^ $ : ← →

숫자G : line숫자로 이동
    e.g. 15G
```

## 1.4 Change to Edit mode
```
i : 커서 왼쪽으로 이동(insert)
I : 행 시작으로 이동

a : 커서 오른쪽으로 이동(append)
A : 행 끝으로 이동

o : 커서 아래로 이동
O : 커서 위로 이동
```


# 2. Modification
## 2.1 Paste
```
p : 커서 앞에 붙여넣기
P : 커서 뒤에 붙여넣기
```

## 2.2 Copy
일반적으로 복사로 copy를 주로 사용하지만 vi editor가 개발될 아주 먼 옛날에는 `c`가 이미 `continue`라는 의미로 사용되고 있었다고한다. \
따라서, copy와 비슷한(?) 개념인 yank(빠르게 물건을 움켜잡아 빼앗는다)의 `y`가 복사를 대표하게 되었다고 한다.

### 2.2.1 Chracater
```
yl : 복사
x  : 잘라내기
```

### 2.2.2 Word
다음 명령어들은 현재 커서가 포함된 단어를 복사하거나 잘라내는데, 전체 단어가 아니라 현재 커서의 위치부터 복사한다. \
어째선지 커서의 위치와 관계없이 전체 단어를 복사하는 키는 없는 것 같다.
```
yw : 복사
dw : 잘라내기 
```

### 2.2.3 Line
```
yy : 복사
dd : 잘라내기
D  : 현재 커서부터 잘라내기
숫자dd : 숫자행만큼 잘라내기
    e.g. 3dd
숫자,숫자d: 해당 행들 잘라내기
    e.g. 15,30d
```
