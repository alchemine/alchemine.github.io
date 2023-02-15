---
title: ps
tags: Linux
---

<!--more-->

Linux에서 `ls`와 더불어 가장 자주 사용하는 명령어로 `ps`를 꼽을 수 있을 것 같아요. <br>
이번 글에서는 `ps`의 몇 가지 option들에 대해서 알아보겠습니다. <br>

---

저는 실행되고 있는 process에 대해 궁금한 경우가 많아서 `r` option을 자주 사용합니다.
```
$ ps r
```

Full format으로 보여주는 `-f` option과 전체 process를 출력하는 `-e` option을 자주 사용하고요. <br>
```
$ ps -ef
```

Process hierarchy를 확인하고 싶은 경우에는 `-H` option을 사용할 수 있습니다. <br>
```
$ ps -eH
```

Process를 실행시킨 user의 정보를 함께 출력하기 위해서는 `-u` option을 사용합니다. <br>
```
$ ps -u
```

그밖의 다양한 option들에 대한 정보는 `--help` 혹은 `man ps`에서 확인하실 수 있습니다.
```
$ ps --help all
$ man ps
```


```
$ ps --help all

Usage:
 ps [options]

Basic options:
 -A, -e               all processes
 -a                   all with tty, except session leaders
  a                   all with tty, including other users
 -d                   all except session leaders
 -N, --deselect       negate selection
  r                   only running processes
  T                   all processes on this terminal
  x                   processes without controlling ttys

Selection by list:
 -C <command>         command name
 -G, --Group <GID>    real group id or name
 -g, --group <group>  session or effective group name
 -p, p, --pid <PID>   process id
        --ppid <PID>  parent process id
 -q, q, --quick-pid <PID>
                      process id (quick mode)
 -s, --sid <session>  session id
 -t, t, --tty <tty>   terminal
 -u, U, --user <UID>  effective user id or name
 -U, --User <UID>     real user id or name

  The selection options take as their argument either:
    a comma-separated list e.g. '-u root,nobody' or
    a blank-separated list e.g. '-p 123 4567'

Output formats:
 -F                   extra full
 -f                   full-format, including command lines
  f, --forest         ascii art process tree
 -H                   show process hierarchy
 -j                   jobs format
  j                   BSD job control format
 -l                   long format
  l                   BSD long format
 -M, Z                add security data (for SELinux)
 -O <format>          preloaded with default columns
  O <format>          as -O, with BSD personality
 -o, o, --format <format>
                      user-defined format
  s                   signal format
  u                   user-oriented format
  v                   virtual memory format
  X                   register format
 -y                   do not show flags, show rss vs. addr (used with -l)
     --context        display security context (for SELinux)
     --headers        repeat header lines, one per page
     --no-headers     do not print header at all
     --cols, --columns, --width <num>
                      set screen width
     --rows, --lines <num>
                      set screen height

Show threads:
  H                   as if they were processes
 -L                   possibly with LWP and NLWP columns
 -m, m                after processes
 -T                   possibly with SPID column

Miscellaneous options:
 -c                   show scheduling class with -l option
  c                   show true command name
  e                   show the environment after command
  k,    --sort        specify sort order as: [+|-]key[,[+|-]key[,...]]
  L                   show format specifiers
  n                   display numeric uid and wchan
  S,    --cumulative  include some dead child process data
 -y                   do not show flags, show rss (only with -l)
 -V, V, --version     display version information and exit
 -w, w                unlimited output width

        --help <simple|list|output|threads|misc|all>
                      display help and exit

For more details see ps(1).
```
