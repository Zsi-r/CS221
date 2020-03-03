#ifndef SEQLIST_H_INCLUDED
#define SEQLIST_H_INCLUDED

#include "list.h"

template<class elemType>
class seqList:public list<elemType>
{
private:
    elemType *data;
    int currentLength;
    int maxSize;
    void doubleSpace();
public:
    seqList(int initSize = 10);
    ~seqList();
    void clear();
    int length() const;
    void insert(int i,const elemType&x);//i 从第0个开始
    void remove(int i);
    int search(const elemType &x)const;
    elemType visit(int i)const;
    void traverse()const;
};

#endif // SEQLIST_H_INCLUDED
