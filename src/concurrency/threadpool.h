#pragma once

#include <thread>
#include <vector>
#include <functional>

class ThreadPool
{
public:
    ThreadPool();

    template<typename T>
    void Add(std::function<void(T)> func, T args);
    void Add(std::function<void()> func);
    void Join();

private:
    std::vector<std::thread> m_Pool;
};