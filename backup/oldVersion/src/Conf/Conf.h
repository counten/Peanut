/*
* Author: micle 2017/12/6
* Env: ubuntu 1710, g++ 4.7
* Copyright (c) www.codeyourlife.cn 
*/

#ifndef MNSERVER_READCONF_H
#define MNSERVER_READCONF_H

#include <iostream>
#include <fstream>
#include <map>

// Inner Project
#include "../Util/StrUtil.h"
#include "../Log/Log.h"

extern std::map<std::string, std::string> mnServerCfg;

extern std::map<std::string, std::string> resMap;



// Define config micro
#define CFG_DEFAULT_FILE "static/Peanut.cfg"
#define CFG_SERVER "server"
#define CFG_SERVER_PORT "port"
#define CFG_SERVER_BACKLOG "backlog"
#define CFG_SERVER_REQSIZE "reqSize"
#define CFG_SERVER_RESSIZE "resSize"

#define CFG_STATIC "static"
#define CFG_STATIC_DIR "dir"
#define CFG_STATIC_FILESIZE "fileSize"

#define CFG_DB "database"
#define CFG_DB_HOST "host"
#define CFG_DB_NAME "dbName"
#define CFG_DB_UNAME "username"
#define CFG_DB_PASSWD "password"
#define CFG_DB_MAXCON "maxCon"

#define CFG_LOG "log"
#define CFG_LOG_DIR "dir"

#define CFG_UPLOAD "upload"
#define CFG_UPLOAD_DIR "dir"

#define CFG_DOWNLOAD "download"
#define CFG_DOWNLOAD_DIR "dir"

class Conf
{
  private:
    std::string confFile;


  public:
    Conf();


    std::string getConfFile();


    void setConfFile(std::string confFile);


    /**
     * @param vector to store confValue;
     * @return 0:success, 1:failed;
     * */
    int readConfAll();


    /**
     * @Desc Init mimeType to map
     * */
    void initMimeType();


    /**
     * @param module
     * @param key
     * @return value map to key
     * */
    std::string getValue(std::string module, std::string key);
};

#endif //MNSERVER_READCONF_H
