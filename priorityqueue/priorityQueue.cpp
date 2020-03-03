#include "priorityQueue.h"

template <class Type>
priorityQueue<Type>::priorityQueue(int capacity)
{
    array = new Type[capacity];
    maxSize = capacity;
    currentSize = 0;
}

template <class Type>
priorityQueue<Type>::~priorityQueue()
{
    delete[] array;
}

template <class Type>
bool priorityQueue<Type>::isEmpty() const
{
    return currentSize == 0;
}

template <class Type>
Type priorityQueue<Type>::getHead() const
{
    return array[1];
}

template <class Type >
void priorityQueue<Type>::enQueue(const Type &x)
{
    if (currentSize == maxSize-1)//因为array[0]不放东西
        doubleSpace();
    
    //向上过滤
    int hole = ++currentSize;
    for (; hole > 1 && x < array[hole / 2]; hole /= 2)
        array[hole] = array[hole / 2];
    array[hole] = x;
}

template <class Type >
Type priorityQueue<Type >::deQueue()
{
    Type miniItem;
    miniItem = array[1];
    array[1] = array[currentSize--];//把最大(maybe)的数放在第一个，再向下过滤
    percolateDown(1);
    return miniItem;
}

template<class Type >
void priorityQueue<Type >:: percolateDown(int hole)//向下过滤
{
    int child;
    Type tmp = array[hole];
    for (; hole * 2 <= currentSize; hole = child){
        child = hole * 2;
        if (child!=currentSize && array[child+1]<array[child])//找小的儿子，如果child==currentSize，则没有右儿子
            child++;
        if(array[child]<tmp)
            array[hole] = array[child];
        else
            break;
    }
    array[hole] = tmp;
}

template <class Type >
void priorityQueue<Type >::buildHeap()
{
    for (int i = currentSize / 2; i > 0;i--)
        percolateDown(i);
}

template <class Type>
priorityQueue<Type>::priorityQueue(const Type *items, int size) : maxSize(size + 10), currentSize(size)
{
    array = new Type[maxSize];
    for (int i = 0; i < size;i++)
        array[i + 1] = items[i];
    buildHeap();
}

template <class Type >
void priorityQueue<Type >::doubleSpace()
{
    Type *tmp = array;
    maxSize *= 2;
    array = new Type[maxSize];
    for (int i = 0; i <= currentSize; i++) //当currentSize == maxSize-1时，调用doubleSpace()
        array[i] = tmp[i];
    delete[] tmp;
}