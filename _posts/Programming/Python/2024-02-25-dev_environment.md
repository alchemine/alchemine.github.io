---
title: Development environment
tags: Python
---

<!--more-->

신뢰성과 일관성 있는 python 코드 작성을 위해 linter로서 [`Ruff`](https://github.com/astral-sh/ruff), code formatter로서 [`Black`](https://github.com/psf/black)을 사용하고 있다. \
이번 글에선 vscode에서 `devcontainer`, `pre-commit`, `ruff`, `black`을 통합하여 자연스럽게 사용할 수 있도록 자동화한 방법에 대해서 소개해보고자 한다.

다양한 기술들과 기능들을 사용하는 것도 좋지만, 무엇보다 중요한 것은 팀 구성원들이 코드에 대한 유지보수에 대한 중요성을 알고 자발적으로 코드의 품질을 높일 수 있도록 독려하는 것이다!

# File structure
```bash
.
├── ...
├── .devcontainer
│   └── devcontainer.json
├── .pre-commit-config.yaml
└── pyproject.toml
```

# 1. Dev container
사용법은 [여기](https://alchemine.github.io/2024/02/05/dev_container.html)를 참고. \
아래와 같이, `devcontainer.json`에서 black formatter와 ruff 등을 파일을 저장할 때마다 사용될 수 있도록 설정할 수 있다.

```
For format details, see https://aka.ms/devcontainer.json. For config options, see the
README at: https://github.com/devcontainers/templates/tree/main/src/docker-existing-dockerfile
```

- `.devcontainer/devcontainer.json`
  ```json
  {
    "name": "Existing Dockerfile",
    "build": {
      "context": "..",
      "dockerfile": "../Dockerfile"
    },
    "customizations": {
      "vscode": {
        "extensions": [
          "ms-python.python",
          "ms-toolsai.jupyter",
          "GitHub.vscode-pull-request-github",
          "esbenp.prettier-vscode",
          "ms-python.black-formatter",
          "eamodio.gitlens",
          "GitHub.copilot",
          "charliermarsh.ruff",
          "elagil.pre-commit-helper"
        ],
        "settings": {
          "terminal.integrated.defaultProfile.linux": "bash",
          "githubIssues.issueBranchTitle": "feature/${issueNumber}-${sanitizedIssueTitle}",
          "editor.formatOnSave": true,
          "editor.defaultFormatter": "esbenp.prettier-vscode",
          "notebook.formatOnSave.enabled": true,
          "notebook.codeActionsOnSave": { "notebook.source.fixAll": true },
          "[python]": {
            "editor.formatOnSave": true,
            "editor.codeActionsOnSave": {
              "source.fixAll": true,
              "notebook.source.fixAll": true,
              "editor.defaultFormatter": "ms-python.black-formatter"
            }
          }
        }
      }
    },
    "features": {
      "ghcr.io/devcontainers/features/docker-outside-of-docker:1": {}
    },
    "mounts": ["source=${localEnv:HOME}/.ssh,target=/root/.ssh,type=bind"],
    "containerEnv": { "": "" },
    "postCreateCommand": ""
  }
  ```

# 2. Pre-commit
- [https://pre-commit.com/](https://pre-commit.com/)

Commit 하기 전, 몇 가지 도구를 자동으로 수행하는 검증 과정을 추가하여 코드의 일관성과 신뢰성을 높일 수 있다.

1. `pre-commit` package 설치
  ```bash
  pip install pre-commit
  ```
2. `.pre-commit-config.yaml` \
pre-commit으로서 사용되는 도구들과 설정들을 해당 파일에서 설정할 수 있다. \
아래와 같이 사용하면 black formatter(python3.9), ruff 등을 commit 수행 시 자동으로 수행하여 코드의 문제점을 체크할 수 있다.

  ```yaml
  # See https://pre-commit.com for more information
  # See https://pre-commit.com/hooks.html for more hooks
  repos:
    - repo: https://github.com/pre-commit/pre-commit-hooks
      rev: v4.5.0
      hooks:
        - id: trailing-whitespace
        - id: end-of-file-fixer
        - id: check-yaml
        - id: check-added-large-files
    - repo: https://github.com/ambv/black
      rev: "24.2.0"
      hooks:
        - id: black
          language_version: python3.9
    - repo: https://github.com/astral-sh/ruff-pre-commit
      rev: v0.2.2
      hooks:
        - id: ruff
          args: [--fix]
  ```
3. Git에 적용
  ```bash
  pre-commit install
  ```

# 3. Ruff
- [https://docs.astral.sh/ruff/](https://docs.astral.sh/ruff/)

Ruff와 관련된 설정 파일은 `pyproject.toml` 혹은 `ruff.toml`로 관리할 수 있다. \
다음은 `pyproject.toml`에 ruff 설정을 추가한 것이다. (ruff의 설정은 [여기](https://velog.io/@ozoooooh/Python-Linter%EB%A1%9C-Ruff%EB%A5%BC-%EC%82%AC%EC%9A%A9%ED%95%B4%EB%B3%B4%EA%B8%B0feat.-pre-commit)를 참고)

- `pyproject.toml`
  ```toml
  [tool.poetry]
  name = "suni-bot-dm"
  version = "0.1.0"
  description = "mySUNI Chatbot - Dialogue Model"
  authors = ["dj-yoon <alchemine@bereview.co.kr>"]
  readme = "README.md"
  
  [tool.poetry.dependencies]
  python = "^3.9"
  
  [build-system]
  requires = ["poetry-core"]
  build-backend = "poetry.masonry.api"
  
  [tool.ruff]
  # ref: https://beta.ruff.rs/docs/rules/
  select = ["B", "C4", "E", "F", "N", "I", "W", "UP"]
  ignore = ["F403","F405","E501","E402"]
  
  # Allow autofix for all enabled rules (when `--fix`) is provided.
  fixable = ["A", "B", "C", "D", "E", "F", "I", "UP"]
  unfixable = []
  
  per-file-ignores = {}
  
  # Same as Black.
  line-length = 88
  
  # Allow unused variables when underscore-prefixed.
  dummy-variable-rgx = "^(_+|(_+[a-zA-Z0-9_]*[a-zA-Z0-9]+?))$"
  
  # Assume Python 3.9.
  target-version = "py39"
  
  [tool.ruff.mccabe]
  # Unlike Flake8, default to a complexity level of 10.
  max-complexity = 10
  ```
