---
layout: article
title: Access remote jupyter-notebook
tags: MachineLearning_Base
sidebar:
  nav: docs-en
---

# Remarks
이 글은 [https://jupyter-notebook.readthedocs.io/en/stable/public_server.html](https://jupyter-notebook.readthedocs.io/en/stable/public_server.html)을 참고하여 작성되었습니다.

<!--more-->

---

### 1. Generate config file

    $ jupyter notebook --generate-config  // ~/.jupyter/jupyter_notebook_config.py 생성

<br>
### 2. Prepare a hashed password

    $ jupyter notebook

      // In one .ipynb
      In [1]: from noteobook.auth import passwd
      In [2]: passwd()
      Enter password:
      Verify password:
      Out[2]: 'sha1:67c9e60bb8b6:9ffede0825894254b2e042ea597d771089e11aed'

<br>
### 3. Adding hashed password to your notebook configuration file

    $ vi ~/.jupyter/jupyter_notebook_config.py

      // jupyter_notebook_config
      // c = get_config()  // 안 될 경우 추가
      c.NotebookApp.ip = '*'
      c.NotebookApp.password = u'sha1:~'
      c.NotebookApp.open_browser = False
      c.NotebookApp.allow_origin = '*'
      c.NotebookApp.notebook_dir = '/workspace'  // 시작 directory

<br>
### 4. Unblocking port

    $ sudo ufw allow 8888

<br>
### 5. Add kernel

    $ source activate [env]
    $ pip install ipykernel
    $ python -m ipykernel install --user --name [env] --display-name "[display name]"

<br>
### 6. Remove kernel and environment

    // Kernel 제거
    $ jupyter kernelspec uninstall [display Name]

    // Env 제거
    $ conda env remove --name [env]
