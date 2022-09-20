#include <ThreadPool.h>

using namespace Core;


void ThreadPool::Loop()
{
    while (1)
    {
        std::function<void()> task;
        {
            std::thread::id id = std::this_thread::get_id();
            lock.lock();
            while (tasks.empty())
            {
                std::this_thread::sleep_for(std::chrono::milliseconds(1));
            }

            task = tasks.front();
            tasks.pop();
            lock.unlock();
        }
        task();
    }
}

ThreadPool::ThreadPool()
{
    int threadMax = std::thread::hardware_concurrency() / 2;
    threads.resize(threadMax);
    for (int i = 0; i < threadMax; i++)
    {
        threads.at(i) = std::thread([=] {Loop(); });
    }
    stop = false;
}

void ThreadPool::Queue(std::function<void() >& job)
{

    //lock.lock();
    tasks.push(job);
    //lock.unlock();
}

bool ThreadPool::Busy()
{
    lock.lock();
    bool busy = tasks.empty();
    lock.unlock();
    return busy;
}



void ThreadPool::Stop()
{
    stop = true;
    lock.lock();
    for (int i = 0; i < threads.size(); i++)
    {
        threads[i].join();
    }
    threads.clear();
    lock.unlock();
}