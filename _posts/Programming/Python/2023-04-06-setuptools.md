---
title: setuptools
tags: Python
---

<!--more-->

`setuptools`를 이용한 python package의 구조에 대하여 알아보자.

가령 `analysis-tools` 라는 이름을 가진 패키지의 기본적인 디렉터리 구조를 다음과 같이 잡을 수 있다.

```bash
analysis-tools
├─analysis_tools
│  └─common
├─docs
├─tests
├─README.md
├─requirements.txt
└─setup.py
```

이제 각 요소에 대해 알아보자.


# 1. Source code
## 1.1 Name of src directory: [a-z_]
Source code가 포함된 디렉터리의 이름은 `-`(hypen)이 포함되지 않도록 한다. \
코드 상에서 `PYTHONPATH` 는 root directory가 되기 때문에 `import`가 용이하도록 하이픈, 공백 등은 제거하는 것이 좋다. \
e.g.
- `scikit-learn` → `sklearn`: [https://github.com/scikit-learn/scikit-learn](https://github.com/scikit-learn/scikit-learn)
- `pandas-datareader` → `pandas_datareader`: [https://github.com/pydata/pandas-datareader](https://github.com/pydata/pandas-datareader)

## 1.2 PYTHONPATH: root directory
Source code 내에서 다른 module, package를 `import` 할 때 root directory를 기반으로 경로를 잡는다. \
따라서, PyCharm의 `Mark Directory as Sources Root` 기능을 사용하거나 `python -m` 옵션을 사용하여 개발을 진행하는 것이 좋다.

## 1.3 \_\_init\_\_.py
내부 패키지/모듈을 유연하게 사용하기 위해 `__init__.py` 를 생성할 필요가 있다.

아래와 같이 `__init__.py` 를 생성해두면, 다음과 같이 module들을 사용할 수 있다.

```python
# analysis_tools/__init__.py

from . import eda
from . import metrics
from . import modeling
from . import preprocessing
from . import random
from . import utils
```

```python
from analysis_tools import eda
from analysis_tools.eda import *
```

내부 패키지에서도 마찬가지로 사용할 수 있다.

```python
# analysis_tools/common/__init__.py

from .config import *
from .env import *
from .plot_utils import *
from .utils import *
```

```python
from analysis_tools.common import *
```


# 2. README.md
패키지에 대한 상세한 설명을 하는 파일


# 3. requirements.txt
패키지에서 사용되는 의존 package list로 다음 명령어를 통해 자동으로 생성할 수도 있다. \
`$ pip freeze > requirements.txt`


# 4. setup.py
패키지에 대한 메타데이터를 정의하는 스크립트로 주로 다음과 같이 사용한다.

```python
from setuptools import setup, find_packages


setup(
    name="analysis-tools",
    version="0.1.0",
    packages=find_packages(),
    install_requires=open("requirements.txt").read(),
    classifiers=[
        "Development Status :: 3 - Alpha",
        "License :: OSI Approved :: MIT License",
        "Programming Language :: Python :: 3",
        "Programming Language :: Python :: 3.6",
        "Programming Language :: Python :: 3.7",
        "Programming Language :: Python :: 3.8",
    ],
    author="Dongjin Yoon",
    author_email="djyoon0223@gmail.com",
    url="https://github.com/djy-git/analysis-tools",
    description="Analysis tools for machine learning projects",
    long_description=open("README.md").read(),
    long_description_content_type="text/markdown",
    license="MIT",
)
```

- `name`\
패키지의 이름
- `version`\
패키지의 버전
- `packages`\
패키지 내의 모듈과 서브 패키지. 패키지나 모듈의 경로를 제대로 찾지 못한다면 이쪽 문제일 가능성이 높다
- `install_requires`\
패키지가 의존하는 다른 패키지의 목록. 미리 만들어둔 `requirements.txt` 를 사용할 수 있다
- `classifiers`\
패키지에 대한 추가 정보를 제공하는 분류자 목록. 개발 상태, 라이선스, 지원되는 Python 버전 등을 포함한다
- `author, author_email`\
패키지 작성자의 이름과 이메일 주소
- `url`\
패키지의 홈페이지 URL
- `description`\
패키지에 대한 짧은 설명
- `long_description`\
패키지에 대한 자세한 설명
- `long_description_content_type`\
long_description의 콘텐츠 형식
- `license`\
패키지에 적용되는 라이선스

명령어를 추가하여 사용하는 방법에 관하여는 [여기를](https://alchemine.github.io/2020/12/09/setuptools_cmd.html) 참고.


# 5. tests
단위 테스트 스크립트들을 `tests` 디렉터리 안에 저장한다. \
Pytest를 사용한다면, 다음의 명령어를 통해 하위에 있는 모든 스크립트들을 체크해볼 수 있다.

`$ python -m pytest`


다음과 같이 `pyenv`를 통해 가상환경을 관리하여 python version 호환성을 유지할 수도 있다.

```bash
# pytest.sh

#!/bin/bash

for version in 3.8.16 3.9.16 3.10.10
do
#  pyenv install $version
  pyenv virtualenv $version test-$version
  source ~/.pyenv/versions/test-$version/bin/activate
  pip install -r requirements.txt —quiet
  python -m pytest
  pyenv uninstall -f test-$version
done
```


# 6. docs
주로 [`sphinx`](https://www.sphinx-doc.org/en/master/)를 이용한 문서화 관련 파일들을 저장한다. \
c.f. [https://github.com/alchemine/base-structure/tree/main/docs](https://github.com/alchemine/base-structure/tree/main/docs)
