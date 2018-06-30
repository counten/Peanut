/*
* Author: micle 2018/3/12
* Env: ubuntu 1604, g++ 5.4
* Copyright (c) www.codeyourlife.cn
*/

#include "cn.codeyourlife.peanut/Database/Pool.h"
//#include "WebAPI/RootersMap.h"
#include "cn.codeyourlife.peanut/Log/Log.h"
#include "cn.codeyourlife.peanut/Conf/Conf.h"
#include "cn.codeyourlife.peanut/Conf/Defination.h"
#include "cn.codeyourlife.peanut/Bin/Peanut.h"
#include "cn.codeyourlife.peanut/Util/StrUtil.h"
#include "WebAPI/RootersMap.h"

using namespace Peanut;

Pool *_dbPool;

int main()
{
    readConfAll();
    logInfo("ServerInit: Read all conf!");

    registerController();
    logInfo("ServerInit: registerController!");

    std::string host = getValue(CFG_DB, CFG_DB_HOST);
    std::string db = getValue(CFG_DB, CFG_DB_NAME);
    std::string uName = getValue(CFG_DB, CFG_DB_UNAME);
    std::string password = getValue(CFG_DB, CFG_DB_PASSWD);
    int maxCon = S2i(getValue(CFG_DB, CFG_DB_MAXCON));
    _dbPool = Pool::getMysqlPoolObject();
    _dbPool->setParameter(host.c_str(), uName.c_str(), password.c_str(), db.c_str(), 0, nullptr, 0, maxCon);
    logInfo("ServerInit: Create dbPool!");

    SchemeEPollThreadPool();
    return 0;
}