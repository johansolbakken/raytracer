#include "concurrency/semaphore.h"

Semaphore::Semaphore(int value)
: m_Counter(value)
{
}

Semaphore::~Semaphore()
{
}

void Semaphore::Wait()
{
    {
        std::unique_lock<std::mutex> lock(m_Mutex);
        while(m_Counter == 0) {
            m_Ready.wait(lock);
        }
        m_Counter--;
    }
}

void Semaphore::Signal()
{
    {
        std::lock_guard<std::mutex> lock(m_Mutex);
        m_Counter++;
        m_Ready.notify_one();
    }
}

int Semaphore::GetCount()
{
    std::lock_guard<std::mutex> lock(m_Mutex);
    return m_Counter;
}
