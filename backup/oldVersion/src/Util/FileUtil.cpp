/*
* Author: micle 2017/12/15
* Env: ubuntu 1710, g++ 4.7
* Copyright (c) www.codeyourlife.cn
*/


#include "FileUtil.h"

FileUtil::FileUtil()
{}


// get file from disk
int FileUtil::get_file_disk(std::string filePath, unsigned char *fileBuf)
{
    int read_count = 0;

    int fd = open(filePath.c_str(), O_RDONLY);
    if (fd == -1)
    {
        Log::logError("get_file_disk:open");
        return -1;
    }
    unsigned long st_size;
    struct stat st;
    if (fstat(fd, &st) == -1)
    {
        Log::logError("get_file_disk:stat");
        return -1;
    }
    st_size = st.st_size;
    int fileSize = StrUtil::suS2i(Conf().getValue(CFG_STATIC, CFG_STATIC_FILESIZE));
    if (st_size > fileSize)
    {
        Log::logError("get_file_disk:File is too large" + filePath);
        return -1;
    }
    if ((read_count = read(fd, fileBuf, fileSize)) == -1)
    {
        Log::logError("get_file_disk:read");
        return -1;
    }
    return read_count;
}