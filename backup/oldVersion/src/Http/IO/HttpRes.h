/*
* Author: micle 2017/12/6
* Env: ubuntu 1710, g++ 4.7
* Copyright (c) www.codeyourlife.cn
*/

#ifndef MNSERVER_HTTPRES_H
#define MNSERVER_HTTPRES_H

#include <iostream>

// Inner Project
#include "../../Util/StrUtil.h"
#include "../../Util/TimeUtil.h"
#include "../../Util/FileUtil.h"

#define RES_OK 200
#define FILE_NOT_FOUND 404      // file not found on server;
#define SERVER_INNOR_ERROR 500  // error in server;

#define SERVER "mnServer(0.1 alpha)/Linux @http://codeyourlife.cn/"
#define HTTP_V1 "HTTP/1.1"
#define CTYPE_TEXT_UTF8 "text/html;charset=UTF-8"
#define NONE_INIT "null"

class HttpRes
{
private:
    std::string protocal;
    int status;
    std::string date;
    std::string server;
    std::string cType;
    std::string allows;
    int cLen;
    std::string strContent;
    unsigned char * content;

public:

    HttpRes();

    /**
     * @return standard response string;
     * */
    int format(unsigned char *send_buf);

    std::string getProtocal();

    void setProtocal(std::string protocal);

    int getStatus();

    void setStatus(int status);

    std::string getDate();

    void setDate(std::string date);

    std::string getServer();

    void setServer(std::string server);

    std::string getCType();

    void setCType(std::string cType);

    std::string getAllows();

    void setAllows(std::string allows);

    int getCLen();

    void setCLen(int cLen);

    std::string getStrContent() const;

    void setStrContent(std::string strContent);

    const unsigned char *getContent();

    void setContent(unsigned char *con);
};


#endif //MNSERVER_HTTPRES_H
