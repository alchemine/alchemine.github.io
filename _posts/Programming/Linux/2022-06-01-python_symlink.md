---
title: Error & Solution | Command 'python' not found
tags: Linux
---

<!--more-->

# Error
Python을 실행시키려고 하면 가끔 `/usr/bin/python` 없이 `/usr/bin/python3`만 존재하는 경우가 있다.

```
root@DESKTOP-HOME:~/project/etc/docker# python

Command 'python' not found, did you mean:

  command 'python3' from deb python3
  command 'python' from deb python-is-python3
```


# Solution
[How to get `python` to run Python 3 in WSL bash?](https://stackoverflow.com/a/68476984) 참고

`update-alternatives`를 이용하여 해결할 수 있다.

```
$ sudo update-alternatives --install /usr/bin/python python $(readlink -f $(which python3)) 3
```
