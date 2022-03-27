#pragma once

#include <thread>
#include <condition_variable>

class Semaphore
{
public:
    Semaphore(int value);
    ~Semaphore();

    void Wait();
    void Signal();
    int GetCount();

private:
    std::condition_variable m_Ready;
    std::mutex m_Mutex;
    int m_Counter;
};
