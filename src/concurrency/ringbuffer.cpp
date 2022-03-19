#include "ringbuffer.h"

#include "renderer/renderer_objects.h"

template class RingBuffer<Job>;
template RingBuffer<Job>::RingBuffer(size_t);
template RingBuffer<Job>::~RingBuffer();
template void RingBuffer<Job>::Add(Job);
template Job RingBuffer<Job>::Get();
template bool RingBuffer<Job>::IsEmpty();

template<typename T>
RingBuffer<T>::RingBuffer(size_t size)
: m_AddReadySemaphore(size), m_GetReadySemaphore(0), m_GetEmptyReady(1), m_Size(size), m_Head(0), m_Tail(0), m_Empty(true)
{
    m_Buffer = new T[size];
}

template<typename T>
RingBuffer<T>::~RingBuffer()
{
    delete m_Buffer;
}

template<typename T>
void RingBuffer<T>::Add(T item)
{
    m_AddReadySemaphore.Wait();

    m_Buffer[m_Head] = item;
    m_Head = (m_Head + 1) % m_Size;

    m_GetEmptyReady.Wait();
    m_Empty = (m_Head - m_Tail == 0);
    m_GetEmptyReady.Signal();

    m_GetReadySemaphore.Signal();
}

template<typename T>
T RingBuffer<T>::Get()
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

template<typename T>
bool RingBuffer<T>::IsEmpty()
{
    bool empty = true;
    m_GetEmptyReady.Wait();
    empty = m_Empty;
    m_GetEmptyReady.Signal();
    return empty;
}