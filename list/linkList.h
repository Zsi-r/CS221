#ifndef LINKLIST_H_INCLUDED
#define LINKLIST_H_INCLUDED

#include "list.h"


//single

template <class elemType>
class sLinkList:public list<elemType>
{
private:
    struct node
    {
        elemType data;
        node *next;

        node(const elemType &x, node *N=NULL){
            data = x; next = N;
        }
        node ():next(NULL){};
        ~node(){};
    };

    node *head;
    int currentLength;

    node *move(int i)const;

public:
    sLinkList();
    ~sLinkList(){clear();delete head;}

    void clear();
    int length()const {return currentLength;}
    void insert(int i,const elemType &x);
    void remove(int i);
    int search(const elemType&x) const;
    elemType visit(int i) const;
    void traverse()const;
};

//double

template <class elemType>
class dLinkList:public list<elemType>
{
private:
    struct node
    {
        elemType data;
        node *prev,*next;

        node(const elemType &x,node *p= NULL , node *n=NULL){
            data = x; next = n;prev = p;
        }
        node ():prev(NULL),next(NULL){};
        ~node(){};
    };

    node *head,*tail;
    int currentLength;

    node *move(int i)const;//返回第i个节点的地址

public:
    dLinkList();
    ~dLinkList(){clear();delete head;delete tail;}

    void clear();
    int length()const {return currentLength;}
    void insert(int i,const elemType &x);
    void remove(int i);
    int search(const elemType&x) const;
    elemType visit(int i) const;
    void traverse()const;
};

#endif // LINKLIST_H_INCLUDED
