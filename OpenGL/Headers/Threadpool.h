#pragma once

#include <vector>
#include <thread>
#include <atomic>
#include <queue>
#include <functional>

namespace Core
{
    class Flag {
    public:
        std::atomic_flag flag = ATOMIC_FLAG_INIT;

        void lock() {
            while (flag.test_and_set());
        }

        void unlock() {
            flag.clear();
        }
    };

    class ThreadPool
    {
    public:
        std::vector<std::thread> threads;
        Flag lock;
        bool stop;
        std::queue<std::function<void()>> tasks;
        ThreadPool();
        void Queue(std::function<void() >& task);
        bool Busy();
        void Stop();
        void Loop();
    };

}