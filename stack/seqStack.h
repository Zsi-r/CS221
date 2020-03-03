#ifndef SEQSTACK_H_INCLUDED
#define SEQSTACK_H_INCLUDED

#include "stack.h"

template <class elemType>
class seqStack:public stack<elemType>
{
private:
    elemType *elem;
    int top_p;
    int maxSize;
    void doubleSpace();
public:
    seqStack(int initSize = 10);
    ~seqStack();
    bool isEmpty() const;
    void push(const elemType &x);
    elemType pop();
    elemType top() const;
};

#endif // SEQSTACK_H_INCLUDED
