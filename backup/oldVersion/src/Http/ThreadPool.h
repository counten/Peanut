/*
* Author: micle 2018/01/29
* Env: debian 9, g++ 4.7
* Copyright (c) www.codeyourlife.cn
*/

#ifndef THREAD_POOL_H
#define THREAD_POOL_H

#include <vector>
#include <queue>
#include <memory>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <future>
#include <functional>
#include <stdexcept>

class ThreadPool
{
private:
    // Workers unit;
    std::vector<std::thread> processors;
    // Tasks queue;
    std::queue<std::function<void()>> tasks;

    // synchronization
    std::mutex queue_mutex;
    std::condition_variable condition;
    bool stop;

public:
    ThreadPool(size_t);

    template <class F, class... Args>
    auto addTask(F &&f, Args &&... args)
    -> std::future<typename std::result_of<F(Args...)>::type>;

    ~ThreadPool();
};


/**
 * @Desc Constructor Init some Processors;
 * */
inline ThreadPool::ThreadPool(size_t num) : stop(false)
{
    for (size_t i = 0; i < num; ++i)
    {
        processors.emplace_back(
                [this] {
                    while (true)
                    {
                        std::function<void()> task;

                        {
                            std::unique_lock<std::mutex> lock(this->queue_mutex);
                            this->condition.wait(lock,
                                                 [this] { return this->stop || !this->tasks.empty(); });
                            if (this->stop && this->tasks.empty())
                            {
                                return;
                            }
                            task = std::move(this->tasks.front());
                            this->tasks.pop();
                        }

                        task();
                    }
                });
    }
}


/**
 * @Desc Add new work item to the pool;
 * */
template <class F, class... Args>
auto ThreadPool::addTask(F &&f, Args &&... args)
-> std::future<typename std::result_of<F(Args...)>::type>
{
    using return_type = typename std::result_of<F(Args...)>::type;

    auto task = std::make_shared<std::packaged_task<return_type()>>(
            std::bind(std::forward<F>(f), std::forward<Args>(args)...));

    std::future<return_type> res = task->get_future();
    {
        std::unique_lock<std::mutex> lock(queue_mutex);

        // don't allow enqueueing after stopping the _pool
        if (stop)
        {
            throw std::runtime_error("enqueue on stopped ThreadPool");
        }

        tasks.emplace([task]() { (*task)(); });
    }
    condition.notify_one();
    return res;
}


/**
 * @Desc The destructor joins all threads;
 * */
inline ThreadPool::~ThreadPool()
{
    {
        std::unique_lock<std::mutex> lock(queue_mutex);
        stop = true;
    }
    condition.notify_all();
    for (std::thread &worker : processors)
    {
        worker.join();
    }
}

#endif