/*
* Author: wbq813 2018/01/22
* Env: debian 9, g++ 4.7
* Copyright (c) www.codeyourlife.cn
*/


#include "gtest/gtest.h"

// Inner Project
#include "../cn.codeyourlife.peanut/Conf/Conf.h"
#include "../cn.codeyourlife.peanut/Database/Pool.h"
#include "../cn.codeyourlife.peanut/Conf/Defination.h"
#include "../cn.codeyourlife.peanut/Util/StrUtil.h"
#include "../cn.codeyourlife.peanut/Util/TimeUtil.h"


/**
 * @Desc Database.Simple DbInsert test;
 * */
TEST(InsertTest, db1)
{
    Peanut::readConfAll();
    std::string url = "hello, DbInsert";
    MYSQL *conn;
    conn = mysql_init(NULL);
    std::string host = Peanut::getValue(CFG_DB, CFG_DB_HOST);
    std::string db = Peanut::getValue(CFG_DB, CFG_DB_NAME);
    std::string uName = Peanut::getValue(CFG_DB, CFG_DB_UNAME);
    std::string password = Peanut::getValue(CFG_DB, CFG_DB_PASSWD);

    bool connect = mysql_real_connect(conn, host.c_str(), uName.c_str(), password.c_str(), db.c_str(), 0, NULL, 0);
    if (connect)
    {
        std::string sql = "insert into test (td, url, date) values ('"
                          + Peanut::getTimestamps()+"', '" + url + "','" + Peanut::getLocalTime() + "')";
        Peanut::logInfo(sql.c_str());
        if (mysql_query(conn, sql.c_str()) == 0)
        {
            Peanut::logSuccess("Database query OK!");
        }
        else
        {
            Peanut::logError("Database query error!");
        }
        mysql_close(conn);
    }
    else
    {
        Peanut::logError("Database connect failed!");
    }
}


void* Handler(void* arg)
{
    long tid = (long)arg;
    std::string query = "select * from authors;";
    QueryResult queryResult = _dbPool->executeSql(query.c_str());

    EXPECT_TRUE(queryResult.getColumnCount() > 0);
    EXPECT_TRUE(queryResult.getRowCount() > 0);
//    std::cout << queryResult.getResultStr()<<"\n";
}

/**
* @Desc read conf and connect db test insert;
*
* */
//TEST(PoolTest, db3)
//{
//    Peanut::readConfAll();
//    std::string host = Peanut::getValue(CFG_DB, CFG_DB_HOST);
//    std::string db = Peanut::getValue(CFG_DB, CFG_DB_NAME);
//    std::string uName = Peanut::getValue(CFG_DB, CFG_DB_UNAME);
//    std::string password = Peanut::getValue(CFG_DB, CFG_DB_PASSWD);
//    int maxCon = Peanut::S2i(Peanut::getValue(CFG_DB, CFG_DB_MAXCON));
//
//    _dbPool = Pool::getMysqlPoolObject();
//    _dbPool->setParameter(host.c_str(),uName.c_str(),password.c_str(),db.c_str(),0,NULL,0,maxCon);
//
//    const int THREAD_COUNT = 2;
//    pthread_t threads[THREAD_COUNT];
//    for (long i = 0; i < THREAD_COUNT; i++)
//    {
//        pthread_create(&threads[i], NULL, Handler, (void *) i);
//        sleep(1);
//    }
//
//    for (int i = 0; i < THREAD_COUNT; i++)
//    {
//        pthread_join(threads[i], 0);
//    }
//}

//TEST(poolTest, db4) {
//    Pool *mysql = Pool::getMysqlPoolObject();
//    mysql->setParameter("47.94.249.60","blogCyl","blogCYL123","blog_cyl",0,NULL,0,20);
//    QueryResult m = mysql->executeSql("select * from blogs");
////    std::cout << m.getResultStr();
//    delete mysql;
//    ASSERT_TRUE(m.getRowCount()>0);
//}