/*
* Author: micle 2018/03/03
* Env: ubuntu 1604, g++ 4.7
* Copyright (c) www.codeyourlife.cn
*/

#include "Pool.h"

#include "../Log/Log.h"

Pool *Pool::_poolObject = NULL;
std::mutex Pool::_objectLock;
std::mutex Pool::_poolLock;

Pool::Pool() {}


/**
 * Set necessary parameters;
 * */
void Pool::setParameter(const char *host,
                        const char *user,
                        const char *password,
                        const char *dbName,
                        unsigned int port,
                        const char *socket,
                        unsigned long client_flag,
                        unsigned int max_connect)
{
    _host = host;
    _user = user;
    _password = password;
    _dbName = dbName;
    _port = port;
    _socket = socket;
    _client_flag = client_flag;
    _MAX_CONNECT = max_connect;
}


/**
 * 有参的单例函数，用于第一次获取连接池对象，初始化数据库信息。
 * */
Pool *Pool::getMysqlPoolObject()
{
    if (_poolObject == NULL)
    {
        _objectLock.lock();
        if (_poolObject == NULL)
        {
            _poolObject = new Pool();
        }
        _objectLock.unlock();
    }
    return _poolObject;
}


/**
 * Create a connection;
 * */
MYSQL *Pool::createOneConnect()
{
    MYSQL *conn = NULL;
    conn = mysql_init(conn);
    if (conn != NULL)
    {
        if (mysql_real_connect(conn,
                               _host,
                               _user,
                               _password,
                               _dbName,
                               _port,
                               _socket,
                               _client_flag))
        {
            _connect_count++;
            // set result charset as UTF8
            mysql_set_character_set(conn, "UTF8");
            return conn;
        }
        else
        {
            Peanut::logError("" + mysql_errno(conn));
            return NULL;
        }
    }
    else
    {
        Peanut::logError("init failed");
        return NULL;
    }
}


/**
 * Judge if the poll is empty;
 * */
bool Pool::isEmpty()
{
    return _pool.empty();
}

/**
 * Get the first connection from _pool;
 * */
MYSQL *Pool::poolFront()
{
    return _pool.front();
}

/**
 * @return Size of the poll;
 * */
unsigned int Pool::poolSize()
{
    return _pool.size();
}


/**
 * Remove an item from beginning;
 * */
void Pool::poolPop()
{
    _pool.pop();
}


/**
 * Get one good connection
 */
MYSQL *Pool::getOneConnect()
{
    _poolLock.lock();
    MYSQL *conn = NULL;
    if (!isEmpty()) {
        // Close lost connection, make sure the first connection is well;
        while (!isEmpty() && mysql_ping(poolFront()))
        {
            mysql_close(poolFront());
            poolPop();
            _connect_count--;
        }
        if (!isEmpty())
        {
            conn = poolFront();
            poolPop();
        }
        else
        {
            if (_connect_count < _MAX_CONNECT)
            {
                conn = createOneConnect();
            }
            else
            {
                Peanut::logError("Connections is too much!" );
            }
        }
    }
    else
    {
        if (_connect_count < _MAX_CONNECT)
        {
            conn = createOneConnect();
        }
        else
        {
            Peanut::logError("Connections is too much!");
        }
    }
    _poolLock.unlock();
    return conn;
}


/**
 * Recycle connection;
 * */
void Pool::close(MYSQL *conn)
{
    if (conn != NULL)
    {
        _poolLock.lock();
        _pool.push(conn);
        _poolLock.unlock();
    }
}


/**
 * @Desc get a connection to execute sql;
 * @return queryResult
 * */
QueryResult Pool::executeSql(std::string sql)
{
    Peanut::logInfo(sql.c_str());
    MYSQL *conn = getOneConnect();
    QueryResult queryResult;

    if (conn)
    {
        if (mysql_query(conn, sql.c_str()) == 0)
        {
            MYSQL_RES *res = mysql_store_result(conn);
            // Store result;
            while (true)
            {
                MYSQL_ROW row;
                if (!(row = mysql_fetch_row(res)))
                {
                    break;
                }
                std::vector<std::string> string_row;
                for (int i = 0; i < mysql_num_fields(res); i++)
                {
                    string_row.push_back(row[i]);
                }
                queryResult.addRow(string_row);
            }
            mysql_free_result(res);
            Peanut::logSuccess("Query OK! ");
        }
        else
        {
            Peanut::logError(mysql_error(conn));
        }
        close(conn);
    }
    else
    {
        Peanut::logError(mysql_error(conn));
    }
    return queryResult;
}


/**
 * DeConstructor, close all connections;
 * */
Pool::~Pool()
{
    while (poolSize() != 0)
    {
        mysql_close(poolFront());
        poolPop();
        _connect_count--;
    }
}