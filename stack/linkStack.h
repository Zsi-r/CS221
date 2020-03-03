#ifndef LINKSTACK_H_INCLUDED
#define LINKSTACK_H_INCLUDED

#include "stack.h"
//不需要头节点，左侧为栈顶（都是从该侧增删），右侧为栈底


template<class elemType>
class linkStack:public stack<elemType>
{
private:
    struct node
    {
        elemType data;
        node *next;
        node(const elemType &x, node *N=NULL)
        {
            data=x;next = N;
        }
        node():next(NULL){};
        ~node(){};
    };

    node *top_p;//指向栈顶的指针，

public:
    linkStack();
    ~linkStack();
    bool isEmpty() const;
    void push(const elemType &x);
    elemType pop();
    elemType top() const;
};

#endif // LINKSTACK_H_INCLUDED
