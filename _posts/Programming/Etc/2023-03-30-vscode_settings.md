---
title: Run python module in Visual Studio Code
tags: Programming_Etc
---

<!--more-->

가슴아프게도 macOS에서 remote server에 지속적으로 deployment를 하면서 사용하면 PyCharm이 맛탱이가 가버리는 문제가 발생한다. \
몇 년 전부터 관련된 문제에 대하여 사람들이 문제 제기를 했었는데 JetBrain측에서는 정확히 증상을 알려달라는 말만 되풀이하고 있는 실정인지라 상당히 실망스러운 상황이 지속되고 있는 중..

결국 vscode로 갈아타게 되었는데 가장 불편한 점이 python file을 실행시킬 때 `-m` option을 기본적으로 제공하지 않는다는 것이었다. 대체 왜? 어떻게 이게 없을 수가 있지? \
다행히 이와 관련된 extension이 있으니 설치하고 `build task` 를 이용하여 어거지로나마 python module을 실행시킬 수 있다.


1. `Command Variable` extension 설치
2. Run python script
    1. `.vscode/tasks.json` 추가
        ```
        {
            // See https://go.microsoft.com/fwlink/?LinkId=733558
            // for the documentation about the tasks.json format
            "version": "2.0.0",
            "tasks": [
                {
                    "label": "Python: Module",
                    "type": "shell",
                    "command": "python -m ${command:extension.commandvariable.file.relativeFileDotsNoExtension}",
                    "problemMatcher": [],
                    "group": {
                        "kind": "build",
                        "isDefault": true
                    }
                }
            ]
        }
        ```
    2. `Tasks: Run Build Task` 실행
3. Debug python script
    1. `.vscode/launch.json` 추가
        ```
        {
            // Use IntelliSense to learn about possible attributes.
            // Hover to view descriptions of existing attributes.
            // For more information, visit: https://go.microsoft.com/fwlink/?linkid=830387
            "version": "0.2.0",
            "configurations": [
                {
                    "name": "Python: Module",
                    "type": "python",
                    "request": "launch",
                    "module": "${command:extension.commandvariable.file.relativeFileDotsNoExtension}",
                    "console": "integratedTerminal"
                }
            ]
        }
        ```
    2. `Debug Python File` 실행