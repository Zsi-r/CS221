#ifndef PRIORITYQUEUE_H_INCLUDED
#define PRIORITYQUEUE_H_INCLUDED
#include "queue.h"
#include <iostream>
//N个节点的完全二叉树高度至多是[logN](down)+1

using namespace std;

template <class Type>
class priorityQueue:public queue<Type>
{
public:
    priorityQueue(int capacity = 100);
    priorityQueue(const Type data[],int size);
    ~priorityQueue();
    bool isEmpty()const;
    void enQueue(const Type &x);
    Type deQueue();
    Type getHead() const;
private:
    int currentSize;
    Type *array;//array[0]不放东西
    int maxSize;

    void doubleSpace();
    void buildHeap();//对一串数字进行有序化建堆
    void percolateDown(int hole);
};


#endif // PRIORITYQUEUE_H_INCLUDED
