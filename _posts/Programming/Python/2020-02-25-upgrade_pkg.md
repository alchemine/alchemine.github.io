---
title: Python package management
tags: Python
---

<!--more-->

## 1. Create / Remove anaconda environment

    // Update all packages in {base}
    (base) $ conda update conda

    // Create environment clonning base
    $ conda create -n {ENV_NAME} --clone {base}

    // Create environment with initial state
    $ conda create -n {ENV_NAME} anaconda

    // Create environment specified python version
    $ conda create -n {ENV_NAME} python=3.7

    // Remove environment
    $ conda env remove -n {ENV_NAME}

## 2. Add / Remove kernel to jupyter notebook

    $ conda activate {ENV_NAME}
    $ pip install ipykernel

    // Add kernel
    $ python -m ipykernel install --user --name {ENV_NAME} --display-name "{DISPLAY_NAME}"

    // Remove kernel
    $ jupyter kernelspec uninstall {DISPLAY_NAME}

## 3. pip upgrade

    $ pip install --upgrade pip

## 4. Anaconda upgrade

    $ conda update conda

## 5. All packages in selected environment upgrade

    // update all packages in {base}
    (base) $ conda update --all

    // update all packages in {ENV_NAME}
    (base) $ conda update -n {ENV_NAME} --all

## 6. Upgrade selected package

    $ pip install --upgrade {PKG_NAME}
    $ conda update {PKG_NAME}
