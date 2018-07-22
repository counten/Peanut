# Peanut

简单的web框架，高性能，模块独立，持续更新(C++).

Simple web backend framework;

High performace, indenpendent modules, updating daily!!

## 文档目录

    backup              // something old or useful
    doc                 // document and design graph
    Peanut              // C++ backend framework

## 运行环境

    CMake 3.4+
    g++ 4.0+
    GNU Make 4.0+


## 特性

1. 工具类:

        字符串工具, 
        文件工具, 
        时间工具, 
        编码转换(solve '@' send to server change to '$40');


1. 独立的配置模块;


    ```
    # mnServer config
    <server>
        port=8080
        backlog=10
        reqSize=1024
        resSize=1050000
    </server>

    # static resource config
    <static>
        dir=blog_cyl/
        home=index.html
        fileSize=2097152
    </static>

    # database config
    <database>
        host=127.0.0.1
        dbName=testdb
        username=admin
        password=admin
        maxCon=100
    </database>
    ```
1. Http;

        epoll + Thread Pool(多路I/O复用加线程池);

1. 数据库模块（MySQL和MariaDB）；

        数据库连接池;
        数据库连接事务；
1. 日志模块

        格式化的日志输出；
        分等级的日志；
        错误信息定位;
1. 格式化返回（以来第三方json模块）；
1. 简单的文件缓存；