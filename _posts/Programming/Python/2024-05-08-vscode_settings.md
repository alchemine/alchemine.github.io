---
title: Visual Studio Code - settings.json
tags: Python
---

<!--more-->

- `.vscode/settings.json`
    ```json
    {
        "extensions": {
          "recommendations": [
            "GitHub.vscode-pull-request-github",
            "esbenp.prettier-vscode",
            "ms-python.black-formatter",
            "ms-toolsai.jupyter",
            "eamodio.gitlens",
            "GitHub.copilot"
          ]
        },
        "terminal.integrated.defaultProfile.linux": "bash",
        "githubIssues.issueBranchTitle": "feature/${issueNumber}-${sanitizedIssueTitle}",
        "editor.formatOnSave": true,
        "editor.defaultFormatter": "esbenp.prettier-vscode",
        "[python]": {
          "editor.defaultFormatter": "ms-python.black-formatter"
        },
        "terminal.integrated.env.windows": {
          "PYTHONPATH": "${workspaceFolder}"
        }
    }
    ```

---

`PYTHONPATH` 설정이 필요하거나, 저장 시 자동으로 black formatter를 사용하도록 하는 세팅으로, `.vscode/settings.json`에 넣어주면 된다.