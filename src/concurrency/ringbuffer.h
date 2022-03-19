#pragma once

#include "semaphore.h"

template<typename T>
class RingBuffer
{
public:
    RingBuffer(size_t size);
    ~RingBuffer();
    void Add(T);
    T Get();
    bool IsEmpty();
    
private:
    int m_Head;
    int m_Tail;
    int m_Size;
    bool m_Empty;

    T* m_Buffer;
    
    Semaphore m_AddReadySemaphore;
    Semaphore m_GetReadySemaphore;
    Semaphore m_GetEmptyReady;
};
