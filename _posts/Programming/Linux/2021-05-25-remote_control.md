---
title: Simple control for remote server
tags: Linux
---

<!--more-->

여러 개의 server를 다루기 위해 간단한 shell script를 만들어 제어할 수 있다.  
비밀번호 입력없이 접속하기 위해 server로 key를 보내는 방법은 [여기](https://alchemine.github.io/2019/10/10/ssh.html#gsc.tab=0)를 참조


`gssh.sh`
{% highlight python linenos %}
#!/bin/bash


CMD=$1
IP="..."
PORTS="..."


for port in "$PORTS"
do
ssh -o StrictHostKeychecking=no root@"$IP" -p "$port" bash <<EOF
source /opt/conda/bin/activate rapids  # activate conda environment
nohup "$CMD" >> nohup.log 2>&1 &
echo Command transmitted to "$IP":"$port"
EOF
done

{% endhighlight %}
