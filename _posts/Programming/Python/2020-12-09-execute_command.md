---
title: Command execution
tags: Python
---

<!--more-->

`python`에서 os의 명령어를 실행시키는 방법이 정말 다양합니다.  
그 중에서도 자주 사용되는 방법으로 `os.system`과 `subprocess.call`이 있는데 [공식 문서](https://docs.python.org/ko/3.7/library/os.html#os.system)에선

> subprocess 모듈은 새 프로세스를 생성하고 결과를 조회하는데, 더욱 강력한 기능을 제공합니다; 이 모듈을 사용하는 것이 이 함수들을 사용하는 것보다 더 바람직합니다.

라고 하며 `subprocess.run`을 권장하고 있습니다.  
`subprocess.call` 은 older API로 호환성을 위해 사용할 수 있습니다. 간단한 사용법은 `run`과 유사하니 [참](https://docs.python.org/ko/3.7/library/subprocess.html#subprocess.run)[고](https://docs.python.org/ko/3.7/library/subprocess.html#subprocess.run)하세요.


{% highlight python linenos %}
from os import system
from subprocess import run
import sys


try:
    # All the same
    retcode = system("mycmd" + " myarg")
    retcode = run("mycmd" + " myarg", shell=True, cwd=".")
    retcode = run(["mycmd" + "myarg"], shell=True, cwd=".")
    
    if retcode < 0:
        print("Child was terminated by signal", -retcode, file=sys.stderr)
    else:
        print("Child returned", retcode, file=sys.stderr)
except OSError as e:
    print("Execution failed:", e, file=sys.stderr)
{% endhighlight %}
