#include "threadpool.h"

ThreadPool::ThreadPool()
{

}

template<typename T>
void ThreadPool::Add(std::function<void(T)> func, T args) 
{
    m_Pool.push_back(std::thread(func, args));
}

void ThreadPool::Add(std::function<void()> func)
{
    m_Pool.push_back(std::thread(func));
}

void ThreadPool::Join()
{
    for (auto& thread : m_Pool)
    {
        thread.join();
    }
}