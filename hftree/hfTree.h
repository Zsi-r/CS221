#ifndef QUEUE_H_INCLUDED
#define QUEUE_H_INCLUDED

#include <iostream>
//两个相加，小的放在右侧
using namespace std;

template<class Type>
class hfTree{
private:
    struct Node {
        Type data;
        int weight;
        int parent,left,right;
    };

    Node *elem;//elem[0]不放东西
    int length;

public:
    struct hfCode{
        Type data;
        string code;
    };

    hfTree(const Type *x,const int *w ,int size);
    void getCode(hfCode result[]);
    ~hfTree(){delete []elem;}
};



#endif // QUEUE_H_INCLUDED