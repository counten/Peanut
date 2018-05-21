/*
* Author: micle 2018/3/13
* Env: ubuntu 1604, g++ 5.4
* Copyright (c) www.codeyourlife.cn
*/

#include "ThreadPool.h"

void ThreadPool::tpLock()
{
    pthread_mutex_lock(&tpLoc_);
    holder_ = pthread_self();
}

void ThreadPool::tpUnLock()
{
    pthread_mutex_unlock(&tpLoc_);
    holder_ = 0;
}

void ThreadPool::tpWait(pthread_cond_t &con)
{
    holder_ = 0;
    pthread_cond_wait(&con, &tpLoc_);
}

bool ThreadPool::isFull()
{
    if (!holder_ == pthread_self())
    {
        return false;
    }
    return maxTaskNum_ > 0 && tasks_.size() >= maxTaskNum_;
}

size_t ThreadPool::queueSize()
{
    tpLock();

    int qSize = tasks_.size();

    tpUnLock();

    return qSize;
}

void *ThreadPool::startThread(void *obj)
{
    // 这里设置为非阻塞，阻塞的时候需要pthread_join回收，否则产生僵尸线程。
    if (0 != pthread_detach(pthread_self()))
    {
        logError("PthreadDetach error");
    }
    ThreadPool *pool = static_cast<ThreadPool *>(obj);
    pool->run();
    return pool;
}

ThreadPool::Task ThreadPool::take()
{
    tpLock();

    while (tasks_.empty())
    {
        tpWait(notEmpty_);
    }
    Task task;
    if (!tasks_.empty())
    {
        task = tasks_.front();
        tasks_.pop_front();
        if (maxTaskNum_ > 0)
        {
            pthread_cond_signal(&notFull_);
        }
    }

    tpUnLock();
    return task;
}

// 每个线程都从start_thread 开始，然后一直执行这个循环，竞争获取任务。
void ThreadPool::run()
{
    while (true)
    {
        Task task(take());
        if (task)
        {
            task();
        }
    }
}

/**
 * @Desc init and create threads;
 * */
ThreadPool::ThreadPool(int threadNum, int maxQueueSize)
        : threadNum_(threadNum), maxTaskNum_(maxQueueSize)
{
    //Init
    holder_ = 0;
    pthread_mutex_init(&tpLoc_, NULL);
    pthread_cond_init(&notEmpty_, NULL);
    pthread_cond_init(&notFull_, NULL);

    if (threadNum < 1 || maxQueueSize < 1)
    {
        exit(1);
    }
    /** Create n threads */
    pthread_t tid_t;
    for (int i = 0; i < threadNum; i++)
    {
        if (0 != pthread_create(&tid_t, NULL, startThread, this))
        {
            logError("PthreadCreate error");
        }
    }
}

ThreadPool::~ThreadPool()
{
    pthread_mutex_destroy(&tpLoc_);
    pthread_cond_destroy(&notFull_);
    pthread_cond_destroy(&notEmpty_);
}

/**
 * @Desc Add task to work list;
 * */
bool ThreadPool::addTask(Task &&task)
{
    {
        tpLock();

        while (isFull())
        {
            tpWait(notFull_);
        }

        if (isFull())
        {
            return false;
        };
        // 将对象的状态或者所有权从一个对象转移到另一个对象，只是转移，没有内存的搬迁或者内存拷贝,性能较好.
        tasks_.push_back(std::move(task));
    }
    pthread_cond_signal(&notEmpty_);
    tpUnLock();
}