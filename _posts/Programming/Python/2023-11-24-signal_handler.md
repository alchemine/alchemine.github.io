---
title: Signal Handler
tags: Python
---

<!--more-->

Python에서 `signal` library를 이용하여 signal을 처리할 수 있다. \
다음과 같이 handler를 포함하는 간단한 class를 만들면 간편하게 signal 처리가 가능하다.


```python
import signal


class SignalHandler:
    """Signal을 처리하는 class
    """
    @classmethod
    def register_signal(cls, signo):
        """Signal을 처리하는 함수를 등록하는 함수

        :param int signo: 처리될 signal(주로 ``signal.SIGINT`` , ``signal.SIGTERM`` 의 형태로 입력)
        """
        signal.signal(signo, cls.handler)

    @staticmethod
    def handler(signo, frame):
        """Signal을 받으면 종료하는 함수 

        :param int signo: 처리될 signal
        :param frame: dummy parameter
        """
        LOGGER.info(f"Receive signal({signo})")
        exit(1)
```

```python
# register SIGINT
SignalHandler.register_signal(signal.SIGINT)
```
