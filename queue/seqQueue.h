#ifndef SEQQUEUE_H_INCLUDED
#define SEQQUEUE_H_INCLUDED

#include "queue.h"
//队空：front == rear; 队满： (rear+1) % MaxSize == front 

template <class elemType>
class seqQueue:public queue<elemType>
{   
    private:
        elemType *elem;
        int maxSize;
        int front, rear;//front 内不存队列元素，牺牲一个单元
        void doubleSpace();
    public:
        seqQueue(int size = 10);
        ~seqQueue();
        bool isEmpty() const;
        void enQueue(const elemType &x);
        elemType deQueue();
        elemType getHead() const;
};

#endif // SEQQUEUE_H_INCLUDED
