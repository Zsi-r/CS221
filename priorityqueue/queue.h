#ifndef QUEUE_H_INCLUDED
#define QUEUE_H_INCLUDED

#include <iostream>

using namespace std;

template <class elemType>
class queue
{
public:
    virtual bool isEmpty() const =0;
    virtual void enQueue(const elemType &x)=0;
    virtual elemType deQueue()=0;
    virtual elemType getHead() const = 0;
    virtual ~queue(){};
};

#endif // QUEUE_H_INCLUDED
