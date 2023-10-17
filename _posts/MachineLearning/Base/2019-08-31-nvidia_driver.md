---
title: NVIDIA Graphic Driver, CUDA, Tensorflow-gpu 설치
tags: MachineLearning_Base
---

# Remarks
**설치환경**: Linux Ubuntu 16.04 (x86_64) <br>
**GPU**: NVIDIA GTX 1080 ti <br>
**NVIDIA Graphic Driver version**: 410.38 (418.56도 가능) <br>
**CUDA Toolkit version**: 10.0 <br>
**Python version**: 3.6.7 <br>
**Tensorflow-gpu version**: 1.14.0 <br>
**설치파일 다운로드 page**: [https://developer.nvidia.com/cuda-10.0-download-archive?target_os=Linux&target_arch=x86_64&target_distro=Ubuntu&target_version=1604&target_type=runfilelocal](https://developer.nvidia.com/cuda-10.0-download-archive?target_os=Linux&target_arch=x86_64&target_distro=Ubuntu&target_version=1604&target_type=runfilelocal)

각각의 version이 호환되지 않으면 제대로 실행되지 않기 때문에 설치 전 먼저 설치하려고 하는 version을 확실히 알아야합니다.

<!--more-->

---

# 1. CUDA 10.0 Toolkit 설치파일 다운로드
[https://developer.nvidia.com/cuda-10.0-download-archive?target_os=Linux&target_arch=x86_64&target_distro=Ubuntu&target_version=1604&target_type=runfilelocal](https://developer.nvidia.com/cuda-10.0-download-archive?target_os=Linux&target_arch=x86_64&target_distro=Ubuntu&target_version=1604&target_type=runfilelocal) 에서 자신의 설정에 잘 맞추어 파일을 다운로드합니다. <br> <br>

`cuda_10.0.130_410.48_linux.run`: 410.38 version graphic driver가 포함된 cuda 10.0 설치파일 <br>
다운받은 설치파일의 실행권한을 얻습니다.

    sudo chmod +x cuda_10.0.130_410.48_linux.run


# 2. Nouveau Driver 제거
Ubuntu에서 기본적으로 깔려있는 **Nouveau** driver와 설치하려는 graphic driver가 충돌하는 문제가 발생하기 때문에 먼저 이를 제거해주어야 합니다. <br>

    $ sudo apt-get update && sudo apt-get upgrade
    $ sudo apt-get remove nvidia* && sudo apt autoremove
    $ sudo apt-get install dkms build-essential linux-headers-generic
    $ sudo vi /etc/modprobe.d/blacklist.conf

      // Append below contents in blacklist.conf
      blacklist nouveau
      blacklist lbm-nouveau
      options nouveau modeset=0
      alias nouveau off
      alias lbm-nouveau off

    $ echo options nouveau modeset=0 | sudo tee -a /etc/modprobe.d/nouveau-kms.conf
    $ sudo reboot


# 3. NVIDIA Graphic Driver 설치
NVIDIA graphic driver를 설치하기 위해선 먼저 linux에서 graphic display와 input device들을 관리하는 X server를 끄고 GUI 관련 서비스들을 종료시켜야 합니다. <br>

    Ctrl + Alt + F1 을 눌러 console창으로 변경 후 로그인합니다

    $ sudo service lightdm stop
    $ cd /path/of/runfile
    $ sudo sh cuda_10.0.130_410.48_linux.run


# 4. 환경변수 추가
CUDA 설치가 되었으면 설치된 cuda library를 읽어올 수 있도록 환경변수를 추가해야 합니다.

    $ vi ~/.bashrc

      // Append below contents in ~/.bashrc
      export PATH=$PATH:/usr/local/cuda-10.0
      export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/usr/local/cuda-10.0/lib64


# 5. CUDA가 제대로 설치가 되었는지 확인합니다.
CUDA 설치 시 sample을 포함했다면 sample code를 빌드하여 검증해볼 수 있습니다.

    $ cd NVIDIA_CUDA-10.0_Samples
    $ cd 0_Simple/asyncAPI
    $ make
    $ ./asyncAPI


# 6. CuDNN 설치
[https://developer.nvidia.com/rdp/form/cudnn-download-survey](https://developer.nvidia.com/rdp/form/cudnn-download-survey)에서 로그인 후 약관에 동의하고 자신의 CUDA version과 환경에 맞는 cuDNN library를 다운로드 합니다. 다운받은 압축파일을 풀고 안에 있는 파일들을 설치한 CUDA 폴더로 옮기면 됩니다.

    $ tar -zxvf cudnn-10.0-linux-x64-v7.6.3.30.tgz
    $ sudo cp cuda/include/cudnn.h /usr/local/cuda-10.0/include
    $ sudo cp cuda/lib64/libcudnn* /usr/local/cuda-10.0/lib64

# 7. Tensorflow-gpu 설치
[https://www.tensorflow.org/install/source#tested_build_configurations](https://www.tensorflow.org/install/source#tested_build_configurations)에서 자신의 CUDA, cuDNN 버전을 확인하고 설치합니다.

    $ pip install tensorflow-gpu


# 8. 검증

    $ python
    > import tensorflow as tf
    > tf.Session()

---

**References** <br>
[http://www.kwangsiklee.com/2017/07/%ec%9a%b0%eb%b6%84%ed%88%ac-16-04%ec%97%90%ec%84%9c-cuda-%ec%84%b1%ea%b3%b5%ec%a0%81%ec%9c%bc%eb%a1%9c-%ec%84%a4%ec%b9%98%ed%95%98%ea%b8%b0/](http://www.kwangsiklee.com/2017/07/%ec%9a%b0%eb%b6%84%ed%88%ac-16-04%ec%97%90%ec%84%9c-cuda-%ec%84%b1%ea%b3%b5%ec%a0%81%ec%9c%bc%eb%a1%9c-%ec%84%a4%ec%b9%98%ed%95%98%ea%b8%b0/)
