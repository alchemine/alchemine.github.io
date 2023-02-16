---
title: Error & Solution | ERROR resolve image config for docker.io/docker/dockerfile:1
tags: Docker
---

<!--more-->

# Error
[Docker overview](https://docs.docker.com/get-started/02_our_app/)를 따라가다 `docker build`를 수행할 때 다음과 같은 에러가 발생하였다. \
Windows-desktop(wsl2)의 설정 때문에 발생한 문제로 보인다.

```
root@DESKTOP-HOME:~/project/etc/docker/getting-started/app# docker build -t getting-started .
[+] Building 0.9s (2/3)
[+] Building 0.9s (3/3) FINISHED
 => [internal] load build definition from Dockerfile                                                                                                    0.0s
 => => transferring dockerfile: 232B                                                                                                                    0.0s
 => [internal] load .dockerignore                                                                                                                       0.0s
 => => transferring context: 2B                                                                                                                         0.0s
 => ERROR resolve image config for docker.io/docker/dockerfile:1                                                                                        0.9s
------
 > resolve image config for docker.io/docker/dockerfile:1:
------
failed to solve with frontend dockerfile.v0: failed to solve with frontend gateway.v0: rpc error: code = Unknown desc = error getting credentials - err: exit status 1, out: ``
```


# Solution
[WSL2: docker build - error getting credentials](https://github.com/docker/for-win/issues/11261#issue-896818817) 참고

1. `Settings` → `Docker Engine`
2. `buildkit: true` → `buildkit: false`

![2022-06-01-docker_build_error_in_wsl2_1](/deprecated/assets/2022-06-01-docker_build_error_in_wsl2_1.jpg)

```
root@DESKTOP-HOME:~/project/etc/docker/getting-started/app# docker build -t getting-started .
/usr/bin/docker-credential-desktop.exe: Invalid argument
Sending build context to Docker daemon  4.654MB
Step 1/7 : FROM node:12-alpine
12-alpine: Pulling from library/node
df9b9388f04a: Pull complete
3bf6d7380205: Pull complete
7939e601ee5e: Pull complete
31f0fb9de071: Pull complete
Digest: sha256:d4b15b3d48f42059a15bd659be60afe21762aae9d6cbea6f124440895c27db68
Status: Downloaded newer image for node:12-alpine
 ---> bb6d28039b8c
Step 2/7 : RUN apk add --no-cache python2 g++ make
 ---> Running in 36c6b44ba998
fetch https://dl-cdn.alpinelinux.org/alpine/v3.15/main/x86_64/APKINDEX.tar.gz
fetch https://dl-cdn.alpinelinux.org/alpine/v3.15/community/x86_64/APKINDEX.tar.gz
(1/22) Installing binutils (2.37-r3)
(2/22) Installing libgomp (10.3.1_git20211027-r0)
(3/22) Installing libatomic (10.3.1_git20211027-r0)
(4/22) Installing libgphobos (10.3.1_git20211027-r0)
(5/22) Installing gmp (6.2.1-r1)
(6/22) Installing isl22 (0.22-r0)
(7/22) Installing mpfr4 (4.1.0-r0)
(8/22) Installing mpc1 (1.2.1-r0)
(9/22) Installing gcc (10.3.1_git20211027-r0)
(10/22) Installing musl-dev (1.2.2-r7)
(11/22) Installing libc-dev (0.7.2-r3)
(12/22) Installing g++ (10.3.1_git20211027-r0)
(13/22) Installing make (4.3-r0)
(14/22) Installing libbz2 (1.0.8-r1)
(15/22) Installing expat (2.4.7-r0)
(16/22) Installing libffi (3.4.2-r1)
(17/22) Installing gdbm (1.22-r0)
(18/22) Installing ncurses-terminfo-base (6.3_p20211120-r0)
(19/22) Installing ncurses-libs (6.3_p20211120-r0)
(20/22) Installing readline (8.1.1-r0)
(21/22) Installing sqlite-libs (3.36.0-r0)
(22/22) Installing python2 (2.7.18-r4)
Executing busybox-1.34.1-r5.trigger
OK: 229 MiB in 38 packages
Removing intermediate container 36c6b44ba998
 ---> 84839e440b7e
Step 3/7 : WORKDIR /app
 ---> Running in 91b4b4384a3c
Removing intermediate container 91b4b4384a3c
 ---> 6469bedbd7e1
Step 4/7 : COPY . .
 ---> f2936cc5ef76
Step 5/7 : RUN yarn install --production
 ---> Running in fe9c40be317d
yarn install v1.22.18
[1/4] Resolving packages...
warning Resolution field "ansi-regex@5.0.1" is incompatible with requested version "ansi-regex@^2.0.0"
warning Resolution field "ansi-regex@5.0.1" is incompatible with requested version "ansi-regex@^3.0.0"
[2/4] Fetching packages...
[3/4] Linking dependencies...
[4/4] Building fresh packages...
Done in 7.97s.
Removing intermediate container fe9c40be317d
 ---> 957ba25b6fae
Step 6/7 : CMD ["node", "src/index.js"]
 ---> Running in 877f59104ec6
Removing intermediate container 877f59104ec6
 ---> c7a322c9be6c
Step 7/7 : EXPOSE 3000
 ---> Running in 0647cd2bedc9
Removing intermediate container 0647cd2bedc9
 ---> 38ec810bf130
Successfully built 38ec810bf130
Successfully tagged getting-started:latest
```
