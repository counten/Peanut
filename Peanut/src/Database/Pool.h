/*
* Author: wbq813 2018/03/03
* Env: ubuntu 1604, g++ 4.7
* Copyright (c) www.codeyourlife.cn
*/

#ifndef MYSQLPOOL_H
#define MYSQLPOOL_H

#include<iostream>
#include<mysql.h>
#include<queue>
#include<map>
#include<vector>
#include<utility>
#include<string>
#include<mutex>
#include<thread>

// Inner Project
#include "QueryResult.h"



class Pool
{
private:
    std::queue<MYSQL *> _pool;                  // queue store conncections
    const char *_host;
    const char *_user;
    const char *_password;
    const char *_dbName;
    unsigned int _port;
    const char *_socket;                        // can be Socket or Pipeline, used to be NULL
    unsigned long _client_flag;
    unsigned int _MAX_CONNECT;                  // Max connection num;
    // new version g++ default of int not 0, make sure to init.
    unsigned int _connect_count = 0;            // Current connection num;
    static std::mutex _objectLock;              // Object lock
    static std::mutex _poolLock;                // Connection pool lock
    static Pool *_poolObject;                   // object

    Pool();

    MYSQL *createOneConnect();

    bool isEmpty();

    MYSQL *poolFront();

    unsigned int poolSize();

    void poolPop();

public:
    ~Pool();

    MYSQL *getOneConnect();

    void close(MYSQL *conn);

    QueryResult executeSql(std::string sql);

    static Pool *getMysqlPoolObject();

    void setParameter(const char *host,
                      const char *user,
                      const char *password,
                      const char *dbName,
                      unsigned int port = 0,
                      const char *socket = NULL,
                      unsigned long client_flag = 0,
                      unsigned int MAX_CONNECT = 50);
    
};

#endif
