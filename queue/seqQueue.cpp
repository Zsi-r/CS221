#include "seqQueue.h"

template <class elemType>
seqQueue<elemType>::seqQueue(int size)
{
    elem = new elemType[size];
    maxSize = size;
    front = rear = 0;
}

template <class elemType>
seqQueue<elemType>::~seqQueue()
{
    delete[] elem;
}

template <class elemType>
bool seqQueue<elemType>::isEmpty()const
{
    return front == rear;
}

template <class elemType>
elemType seqQueue<elemType>::deQueue()//front所指空间没有数据data
{
    front = (front + 1) % maxSize;
    return elem[front];
}

template <class elemType>
elemType seqQueue<elemType>::getHead()const
{
    return elem[(front + 1) % maxSize];
}

template <class elemType>
void seqQueue<elemType>::enQueue(const elemType &x)
{
    if ((rear+1)%maxSize==front)
        doubleSpace();
    rear = (rear + 1) % maxSize;
    elem[rear] = x;
}

template <class elemType>
void seqQueue<elemType>::doubleSpace()
{
    elemType *tmp = elem;
    elem = new elemType[2 * maxSize];
    for (int i = 1; i < maxSize;++i)
    {
        elem[i] = tmp[(front+i)%maxSize];
    }
    front = 0;
    rear = maxSize;
    maxSize *= 2;
    delete tmp;
}