/*
* Author: wbq813 2018/3/13
* Env: ubuntu 1604, g++ 5.4
* Copyright (c) www.codeyourlife.cn
*/

#ifndef _THREAD_POOL_H_
#define _THREAD_POOL_H_

#include <list>
#include <iostream>
#include <functional>

#include "../Log/Log.h"


using namespace Peanut;

class ThreadPool {

public:
    using Task = std::function<void()>;

    /**
     * @Desc init and create threads;
     * */
    ThreadPool(int threadNum, int maxTaskNum);

    ~ThreadPool();

    /**
     * @Desc Add task to work list;
     * */
    bool addTask(Task &&);

private:
    // Num of thread;
    int threadNum_;

    int maxTaskNum_;

    // Task list
    std::list<Task> tasks_;

    pthread_cond_t notEmpty_;

    pthread_cond_t notFull_;

    pthread_mutex_t tpLoc_;

    pthread_t holder_;

    void tpLock();

    void tpUnLock();

    void tpWait(pthread_cond_t &);

    bool isFull();

    size_t queueSize();

    Task take();

    void run();

    static void *startThread(void *arg);
};

#endif
