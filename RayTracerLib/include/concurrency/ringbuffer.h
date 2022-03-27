#pragma once

#include "semaphore.h"

template<typename T>
class RingBuffer
{
public:
    explicit RingBuffer(size_t size)
    : m_AddReadySemaphore(size), m_GetReadySemaphore(0), m_GetEmptyReady(1), m_Size(size), m_Head(0), m_Tail(0), m_Empty(true)
    {
        m_Buffer = new T[size];
    }

    ~RingBuffer()
    {
        delete m_Buffer;
    }

    void Add(T item)
    {
        m_AddReadySemaphore.Wait();

        m_Buffer[m_Head] = item;
        m_Head = (m_Head + 1) % m_Size;

        m_GetEmptyReady.Wait();
        m_Empty = (m_Head - m_Tail == 0);
        m_GetEmptyReady.Signal();

        m_GetReadySemaphore.Signal();
    }

    T Get() const
    {
        m_GetReadySemaphore.Wait();

        T item = m_Buffer[m_Tail];
        m_Tail = (m_Tail + 1) % m_Size;

        m_GetEmptyReady.Wait();
        m_Empty = (m_Head - m_Tail == 0);
        m_GetEmptyReady.Signal();

        m_AddReadySemaphore.Signal();

        return item;
    }

    bool IsEmpty() const
    {
        bool empty = true;
        m_GetEmptyReady.Wait();
        empty = m_Empty;
        m_GetEmptyReady.Signal();
        return empty;
    }
    
private:
    int m_Head;
    mutable int m_Tail;
    int m_Size;
    mutable bool m_Empty;

    T* m_Buffer;
    
    mutable Semaphore m_AddReadySemaphore;
    mutable Semaphore m_GetReadySemaphore;
    mutable Semaphore m_GetEmptyReady;
};
