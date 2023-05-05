---
title: pytest
tags: Python
---

<!--more-->

신나게 키보드를 두드리며 코딩하고 난 다음, 매우 귀찮지만 반드시 해야할 일이 있으니.. \
바로 **코드 검증** 작업이다. \
Python 코드 검증을 위한 라이브러리로 `pytest`, `pylint`, `mypy`, `unittest` 등이 있는데, 이 중에서 가장 많이 사용되는 `pytest` 를 사용하는 방법에 대해 알아보자.


# 1. Project Structure
다음은 `poetry`를 이용하여 생성된 프로젝트의 기본 구조를 약간 변형한 것이다. \
`poetry`와 관련된 내용은 [여기](https://alchemine.github.io/2023/04/07/poetry.html)를 참조.

```bash
poetry-demo
├── pyproject.toml
├── README.md
├── poetry_demo
│   ├── common
│   │   ├── __init__.py
│   │   ├── env.py
│   │   └── utils.py
│   ├── __init__.py
│   └── computer.py
└── tests
    ├── test_common
    │   ├── test_env.py
    │   └── test_utils.py
    └── test_computer.py
```

위와 같은 구조에서 기능 구현에 해당하는 코드들은 `poetry_demo` 이하의 스크립트들이다. \
각각의 스크립트는 분리된 기능을 구현하는 함수와 클래스를 가지고 있을 것이다.

코드 검증을 위해 추가적인 디렉터리 `tests`를 다음과 같이 구성한다.

1. 소스코드(`poetry_demo`)와 동일한 구조를 `tests` 아래에 생성
2. 모든 모듈 및 패키지의 이름 앞에 `test_` 를 추가


# 2. Test code
생성한 `test_*` 모듈들에는 직접 만든 테스트 케이스와 검증 코드가 들어간다.

다음과 같이 검증 코드를 구현할 수 있다.

1. `tests` 이하의 모든 모듈, 패키지, 함수의 이름의 앞에 `test_` 추가
    - 단, class의 이름은 CamelCase 형식을 맞춰 `Test` 추가
2. 생성한 test 함수들의 input argument는 제거
    - 단, method는 `self` 추가
3. 생성한 test 함수들에 구현 코드의 결과를 `assert` 를 이용하여 검증

가령 다음과 같이 구현하면 된다.

```python
# poetry_demo/computer.py

import numpy as np


def prices2returns(prices):
    returns = np.zeros_like(prices)
    returns[1:] = prices[1:] / prices[:-1] - 1
    return returns


class Calculator:
    def add(self, x, y):
        return x + y
    
    @classmethod
    def subtract(cls, x, y):
        return x - y

    @staticmethod
    def multiply(x, y):
        return x * y
```

```python
# tests/test_computer.py

from poetry_demo.computer import *
import numpy as np


def test_prices2returns():
    prices = [1, 2, 4, 8]
    answer = [0, 1, 1, 1]

    result = prices2returns(prices)
    assert np.isclose(result, answer)


class TestCalculator:
    def test_add(self):
        result = Calculator().add(2, 3)
        assert np.isclose(result, 5)

    def test_subtract(self):
        result = Calculator.subtract(5, 2)
        assert np.isclose(result, 3)

    def test_multiply(self):
        result = Calculator.multiply(5, 2)
        assert np.isclose(result, 10)
```

## 2.1 Fixture
기본적으로 `test_*()` 함수는 input을 가지지 않는다. \
그러나 동일한 input을 만드는 과정이 중복되는 경우, `pytest.fixture` 를 사용하여 이를 방지할 수 있다.

```python
# tests/test_computer.py
from poetry_demo.computer import *
import numpy as np
import pytest


@pytest.fixture
def calculator():
    return Calculator()


class TestCalculator:
    def test_add(self, calculator):
        result = calculator.add(2, 3)
        assert np.isclose(result, 5)

    def test_subtract(self):
        result = Calculator.subtract(5, 2)
        assert np.isclose(result, 3)

    def test_multiply(self):
        result = Calculator.multiply(5, 2)
        assert np.isclose(result, 10)
```

여기서 포인트는 2가지이다.

1. `fixture` decorator로 생성한 함수의 이름을 함수(method)의 argument로 사용할 수 있다. (`self, calculator`)
2. `fixture` 로 만든 input을 사용하지 않아도 된다. (`self` 만 사용)

만약 `fixture`를 만드는 작업이 꽤 복잡하다면, 다른 파일로 분리할 수도 있다.

```python
# tests/conftest.py

from poetry_demo.computer import *
import pytest


@pytest.fixture
def calculator():
    return Calculator()
```

```python
# tests/test_computer.py

from poetry_demo.computer import *
import numpy as np


class TestCalculator:
    def test_add(self, calculator):
        result = calculator.add(2, 3)
        assert np.isclose(result, 5)

    def test_subtract(self):
        result = Calculator.subtract(5, 2)
        assert np.isclose(result, 3)

    def test_multiply(self):
        result = Calculator.multiply(5, 2)
        assert np.isclose(result, 10)
```

꽤나 다양하게 사용할 수 있는 `fixture` 와 관련된 자세한 내용은 [여기](https://docs.pytest.org/en/7.2.x/how-to/fixtures.html#override-fixtures)로.


# 3. Pytest
테스트 코드가 완성되었다면 `pytest` 를 실행시킨다. \
기본적으로 현재 위치한 디렉터리 내부의 모든 `test_*.py` 코드들에 대하여 검증이 수행된다.

`PYTHONPATH` 를 root directory로 고정시키고 코드를 짰다면 모듈로 실행시켜야할 것이고,

```bash
$ python -m pytest
```

그렇지 않다면 그냥 돌려도 된다.

```bash
$ pytest
```

추가적으로,

1. 만약 stdout 내용을 보고 싶다면, `-s` option을 통해 확인할 수 있다.
    ```bash
    $ python -m pytest -s
    $ pytest -s
    ```
2. 특정 디렉터리만 테스트하고 싶다면 뒤에 디렉터리를 적어준다.
    ```bash
    $ python -m pytest tests
    $ pytest tests
    ```

`pytest`의 결과는 모든 테스트 함수 중 몇 개가 통과했는지 알려준다.

```bash
====================================== test session starts =======================================
platform linux -- Python 3.8.16, pytest-7.2.2, pluggy-1.0.0
rootdir: poetry-example
collected 1 item

tests/test_main.py .                                                                       [100%]

======================================= 1 passed in 0.17s ========================================
```


# 4. Python compatibility
테스트 코드를 잘 만들어두면 여러 python version 과의 코드 호환성을 유지하기 쉽다.

`pyenv` 와 `poetry` 를 이용하여 가상환경을 만들고 `pytest` 를 통해 코드 검증을 함으로써 어느정도 코드 호환성을 보장할 수 있다.

```bash
# test.sh

#!/bin/bash

for version in 3.8.16 3.9.16 3.10.10
do
    # pyenv install $version
    pyenv virtualenv $version test-$version
    source ~/.pyenv/versions/test-$version/bin/activate
    poetry install --no-root
    python -m pytest
    pyenv uninstall -f test-$version
done
```
