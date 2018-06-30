/*
* Author: micle 2017/12/6
* Env: ubuntu 1710, g++ 4.7
* Copyright (c) www.codeyourlife.cn
*/


#include "Http/Tcp.h"
#include "Database/Pool.h"

Pool *mnPool;

int main()
{
    Conf conf;
    conf.readConfAll();
    conf.initMimeType();
    Log::logInfo("ServerInit: readConf");

    registerController();
    Log::logInfo("ServerInit: registerController");


    std::string host = conf.getValue(CFG_DB, CFG_DB_HOST);
    std::string db = conf.getValue(CFG_DB, CFG_DB_NAME);
    std::string uName = conf.getValue(CFG_DB, CFG_DB_UNAME);
    std::string password = conf.getValue(CFG_DB, CFG_DB_PASSWD);
    int maxCon = StrUtil::suS2i(conf.getValue(CFG_DB, CFG_DB_MAXCON));
    mnPool = Pool::getMysqlPoolObject();
    mnPool->setParameter(host.c_str(),uName.c_str(),password.c_str(),db.c_str(),0,NULL,0,maxCon);
    Log::logInfo("ServerInit: dbPool");

    int s = Tcp::createSocket();
    Log::logInfo("ServerInit: createSocket");

    Log::logSuccess("ServerInit Finished");
    if (0 == Tcp::Bind(s)) {
        Tcp::Listen(s);
    }
    return 0;
}
