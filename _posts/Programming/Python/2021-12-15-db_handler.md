---
title: Multi Database Handler (Singleton)
tags: Python
---

<!--more-->

DB에 접근할 때마다 connection을 생성하면 결국 "누구야!!" 소리가 나온다. \
다음과 같이 Singleton 패턴을 통해 DB에 접근하는 connection의 개수를 제한하면 관리하기 편하다.

일반적으로 하나의 DB 정보만을 다루는 예제 코드들이 대부분인데 여기선 다수의 DB에 접근을 관리할 수 있는 MySQL DB handler를 만들어보았다. 조금 복잡해지긴했지만 두고두고 사용할 것 같다.

이후 transaction 처리까지 수행하는 `read()`, `write()` method도 추가할 예정.


{% highlight python linenos %}
import pymysql


class DBHandler:
    db_infos = []
    instances = []
    conns = []

    def __new__(cls, db_info):
        ids = {'user', 'password', 'host', 'port', 'db'}
        assert ids.issubset(set(db_info)), f"{set(db_info)} should include {ids}"

        if db_info in cls.db_infos:
            instance = cls.instances[cls.db_infos.index(db_info)]
        else:
            instance = super().__new__(cls)  # generate new instance
            cls.db_infos.append(db_info)
            cls.instances.append(instance)
        return instance
    def __init__(self, db_info):
        self.db_info = db_info
        self.idx_info = self.db_infos.index(db_info)
    def __del__(self):
        for conn in self.conns:
            conn.close()

    def get_connection(self):
        if self.idx_info == len(self.conns):
            try:
                conn = pymysql.connect(**self.db_info)
                self.conns.append(conn)
                print(f"[New connection succeeded] {self.db_info['user']}@{self.db_info['host']}:{self.db_info['port']} DB: {self.db_info['db']}")
            except Exception as e:
                print(f"[Connection failed] {self.db_info['user']}@{self.db_info['host']}:{self.db_info['port']} DB: {self.db_info['db']}")
                print(e)
                exit()
        else:
            print(f"[Load existing connection] {self.db_info['user']}@{self.db_info['host']}:{self.db_info['port']} DB: {self.db_info['db']}")
        return self.conns[self.idx_info]

    
DB_INFO = dict(host=...,
               port=...,  # should be of type int
               user=...,
               password=...,
               db=...)
dbHandler1 = DBHandler(DB_INFO)
dbHandler2 = DBHandler(DB_INFO)

print("1. get_connection()")
conn11 = dbHandler1.get_connection()
conn12 = dbHandler1.get_connection()
conn21 = dbHandler2.get_connection()
conn22 = dbHandler2.get_connection()

print("\n2. id(conn)")
for conn in (conn11, conn12, conn21, conn22):
    print("id:", id(conn), conn)
{% endhighlight %}


```
1. get_connection()
[New connection succeeded] ...
[Load existing connection] ...
[Load existing connection] ...
[Load existing connection] ...

2. id(conn)
id: 140374430273344 <pymysql.connections.Connection object at 0x7fab780d4f40>
id: 140374430273344 <pymysql.connections.Connection object at 0x7fab780d4f40>
id: 140374430273344 <pymysql.connections.Connection object at 0x7fab780d4f40>
id: 140374430273344 <pymysql.connections.Connection object at 0x7fab780d4f40>
```

{% highlight python linenos %}
DB_INFO = dict(host=...,
               port=...,
               user=...,
               password=...,
               db=...)
dbHandler3 = DBHandler(DB_INFO)

DB_INFO = dict(host=...,
               port=...,
               user=...,
               password=...,
               db=...)
dbHandler4 = DBHandler(DB_INFO)

print("1. get_connection()")
conn11 = dbHandler3.get_connection()
conn12 = dbHandler3.get_connection()
conn21 = dbHandler4.get_connection()
conn22 = dbHandler4.get_connection()

print("\n2. id(conn)")
for conn in (conn11, conn12, conn21, conn22):
    print("id:", id(conn), conn)
{% endhighlight %}


```
1. get_connection()
[Load existing connection] ...
[Load existing connection] ...
[New connection succeeded] ...
[Load existing connection] ...

2. id(conn)
id: 140374430273344 <pymysql.connections.Connection object at 0x7fab780d4f40>
id: 140374430273344 <pymysql.connections.Connection object at 0x7fab780d4f40>
id: 140374434502496 <pymysql.connections.Connection object at 0x7fab784dd760>
id: 140374434502496 <pymysql.connections.Connection object at 0x7fab784dd760>
```