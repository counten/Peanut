/*
* Author: micle 2017/12/20
* Env: ubuntu 1710, g++ 4.7
* Copyright (c) www.codeyourlife.cn
*/

#ifndef MNSERVER_LOG_H
#define MNSERVER_LOG_H

#include <iostream>

namespace Log{

    /**
     * log Error info
     * */
    template <class T> T logError(T inStr)
    {
        std::string outStr = "[ERROR] ";
        outStr.append(inStr);
        outStr.append("\n");
        std::cout << outStr;
    }

    /**
     * log Warning info
     * */
    template <class T> T logWarning(T inStr)
    {
        std::string outStr = "[WARN] ";
        outStr.append(inStr);
        outStr.append("\n");
        std::cout << outStr;
    }

    /**
     * log Common info
     * */
    template <class T> T logInfo(T inStr)
    {
        std::string outStr = "[INFO] ";
        outStr.append(inStr);
        outStr.append("\n");
        std::cout << outStr;
    }

    /**
     * log Success info
     * */
    template <class T> T logSuccess(T inStr)
    {
        std::string outStr = "[BINGO] ";
        outStr.append(inStr);
        outStr.append("\n");
        std::cout << outStr;
    }
}



#endif //MNSERVER_LOG_H

