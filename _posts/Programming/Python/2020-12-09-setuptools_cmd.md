---
title: Command in setuptools
tags: Python
---

<!--more-->

python 배포를 지원해주는 library가 있는데 바로 `setuptools`입니다.  
`setuptools`를 통해 배포자의 정보와 project의 description, 사용법 등을 손쉽게 제공할 수 있습니다.  


{% highlight python linenos %}
# setup.py

from setuptools import find_packages, setup, Command
from subprocess import run


### Long description is in 'README.md'
with open("README.md", "r") as f:
    long_description = f.read()


### Permitted commands
class MainCommand:
    user_options = []
    def initialize_options(self): pass
    def finalize_options(self): pass

    @staticmethod
    def run_main(option=""):
        run(["python", "main.py", option], cwd="src")

class Run(MainCommand, Command):
    description = "Run src/main.py run"
    def run(self):
        super().run_main('run')
        
class Reset(MainCommand, Command):
    description = "Run src/main.py reset"
    def run(self):
        super().run_main('reset')


### Setup summary
setup(
    name="Base project",
    author="Dongjin Yoon",
    author_email="djyoon0223@gmail.com",
    description="Short description of the project",
    long_description=long_description,
    long_description_content_type="text/markdown",
    url="...",
    packages=find_packages(),  # `requirements.txt` is preferred
    classifiers=[
        "Programming Language :: Python :: 3",
        "Environment :: GPU :: NVIDIA CUDA :: 10.2",
        "Operating System :: POSIX :: Linux"
    ],
    python_requires=">=3.7",
    cmdclass={
        "run"   : Run,
        "reset" : Reset,
    }
)
{% endhighlight %}


이렇게 생성한 `setup.py` 뒤에 `cmdclass`에서 설정해준 명령어를 추가하면 정해진 명령을 수행할 수 있습니다.

```
$ python setup.py run
$ python setup.py reset
```
