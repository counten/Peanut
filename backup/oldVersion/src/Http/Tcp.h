/*
* Author: micle 2017/12/12
* Env: ubuntu 1710, g++ 4.7
* Copyright (c) www.codeyourlife.cn
*/

#ifndef MNSERVER_TCP_H
#define MNSERVER_TCP_H

#include <string.h>

#include <sys/socket.h>
#include <netinet/in.h>

// Inner Project
#include "../Conf/Conf.h"
#include "../Util/StrUtil.h"
#include "../Http/Dispatcher/Dispatcher.h"
#include "../Log/Log.h"
#include "Frame.h"


namespace Tcp
{
    /**
     * @return socket created base on current config, -1 means create failed;
     * */
    int createSocket();

    /**
     * bind port with socket;
     * @return 0:success, 1:failed;
     * */
    int Bind(int sock);


    /**
     * Listen the sock after bind success;
     * @param sock;
     * @return 0:success, 1:failed;
     * */
    int Listen(int sock);

};


#endif //MNSERVER_TCP_H
