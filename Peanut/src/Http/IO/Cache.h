/*
* Author: wbq813 2018/3/13
* Env: ubuntu 1604, g++ 5.4
* Copyright (c) www.codeyourlife.cn
*/

#ifndef _CACHE_H_
#define _CACHE_H_

#include <iostream>
#include <map>
#include <memory>
#include <mutex>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>


#include "../../Conf/Defination.h"
#include "../../Log/Log.h"


class FileInfo
{
public:
    /** address info */
    void *add_;

    /** file size */
    int size_;

    FileInfo(std::string& fileName, int fileSize)
	{
		int srcFd = open(fileName.c_str(), O_RDONLY, 0);
		if(srcFd < 0)
		{
			Peanut::logError("Open error");
		}
		size_ = fileSize;
		if ((add_ = mmap(0, fileSize, PROT_READ, MAP_PRIVATE, srcFd, 0)) == ((void *)-1))
		{
			Peanut::logError("mmap error");
		}

		if(0 > close(srcFd))
		{
			Peanut::logError("Close error");
		}
    }

    ~FileInfo() {
        /** Remove map*/
		if (munmap(add_, size_) < 0)
		{
			Peanut::logError("munMap error");
		}
	}
};


class Cache
{
private:
	/** Router between name and address */
	std::map<std::string, std::shared_ptr<FileInfo>> cache_;

	/** cache 100 file is Most */
	static const size_t MAX_CACHE_SIZE = 100;

	std::mutex mutex_;

public:
	Cache() : mutex_(){}

	/** ThreadSafe getFileAdd */
	void getFileAdd(std::string fileName, int fileSize, std::shared_ptr<FileInfo> &ptr)
	{
		// Find in cache first;
		if (cache_.end() != cache_.find(fileName)) {
			ptr = cache_[fileName];
			return;
		}

		// If cache is full remove the oldest;
		if (cache_.size() >= MAX_CACHE_SIZE) {
			cache_.erase(cache_.begin());
		}

		// Not in cache, try to open it and add to cache;
		ptr = std::make_shared<FileInfo>(fileName, fileSize);
		cache_[fileName] = ptr;
	}
};

#endif /* _CACHE_H_ */
