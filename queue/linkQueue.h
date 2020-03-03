#ifndef LINKQUEUE_H_INCLUDED
#define LINKQUEUE_H_INCLUDED

#include "queue.h"
//没有头尾节点
//front 是队首，左侧，用来出队；rear 是队尾，右侧，用来入队
// 进队时队空与队不空的操作不同

template <class elemType>
class linkQueue:public queue<elemType>
{
    private:
    struct node{
        elemType data;
        node *next;
        node (const elemType &x, node *N = NULL)
        {
            data=x;next=N;
        }
        node() : next(NULL) {};
        ~node() {};
    };

    node *front,*rear;//队不空时，front和rear都有数据，当队长为1时，front和rear所指相同

    public:
    linkQueue();
    ~linkQueue();
    bool isEmpty()const ;
    void enQueue(const elemType&x);
    elemType deQueue();
    elemType getHead()const;
};

#endif // LINKQUEUE_H_INCLUDED
