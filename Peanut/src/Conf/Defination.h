/*
* Author: wbq813 2018/3/13
* Env: ubuntu 1604, g++ 5.4
* Copyright (c) www.codeyourlife.cn
*/

#ifndef _DEFINATION_H_
#define _DEFINATION_H_

#include <map>

// Inner project
#include "../Database/Pool.h"
#include "../Http/IO/Cache.h"
#include "../Http/IO/ReqInfo.h"
#include "../Util/Json.hpp"
#include "../Util/Hash.h"


/**
 * @Desc Micro
 * */
namespace Peanut
{

// Define config micro
#define CFG_FILE "Peanut.cfg"
#define CFG_SERVER "server"
#define CFG_SERVER_PORT "port"
#define CFG_SERVER_BACKLOG "backlog"
#define CFG_SERVER_REQSIZE "reqSize"
#define CFG_SERVER_RESSIZE "resSize"

#define CFG_STATIC "static"
#define CFG_STATIC_DIR "dir"
#define CFG_STATIC_HOME "home"
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

#define MAX_EVENT_NUM 100

    // Request method
#define METHOD_GET "GET"
#define METHOD_POST "POST"
#define METHOD_PUT "PUT"
#define METHOD_DELETE "DELETE"
#define METHOD_HEAD "HEAD"
#define METHOD_TRACE "TRACE"
#define METHOD_OPTIONS "OPTIONS"

/*********************************************************************************/
/**
 * @Desc Enum
 * */

// State of Request parse
    enum class RequestParseState
    {
        ExpectReqLine,
        ExpectHeaders,
        ExpectBody,
        GotAll,
        Error
    };

    enum HttpHandleState
    {
        ExpectReset, // Need Init;
        ExpectRead, // Reading;
        ExpectWrite, // Writing;
        Error,
        Success,
        Closed // Client closed connection;
    };

}

/** Global value*/
// conf value;
extern std::map<std::string, std::string> _confValue;

// database pool;
extern Pool *_dbPool;

// static file cache;
class Cache;
extern Cache _staticFileCache;

// WebAPI use;
typedef std::string (*pController)(ReqInfo);
extern std::map<std::string, pController> _controllerMap;

// json rename;
using _json = nlohmann::json;

// Session;
extern bool _isSessionOn;
extern StringHash _sessionMap;


#endif
