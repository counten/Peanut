/*
* Author: micle 2017/12/6
* Env: ubuntu 1710, g++ 4.7
* Copyright (c) www.codeyourlife.cn
*/

#ifndef MNSERVER_FILEUTIL_H
#define MNSERVER_FILEUTIL_H

#include <sstream>
#include <fstream>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <cstring>

// Inner Project
#include "../Log/Log.h"
#include "../Conf/Conf.h"


class FileUtil
{
public:
    FileUtil();

    /**
     * @param filePath;
     * @param String to store content of file;
     * @return 0:success, 1:failed;
     * */
    int get_file_disk(std::string filePath, unsigned char *fileBuf);
};


#endif //MNSERVER_FILEUTIL_H
