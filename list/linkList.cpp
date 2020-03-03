#include"linkList.h"

//single

template<class elemType>
typename sLinkList<elemType>::node *sLinkList<elemType>::move(int i)const
{
    node *p = head;
    while(i-->=0)p = p->next;
    return p;
}

template<class elemType>
sLinkList<elemType>::sLinkList()
{
    head = new node;
    currentLength = 0;
}

template<class elemType>
void sLinkList<elemType>::clear()
{
    node *p = head -> next,*q;
    head ->next = NULL;
    while (p!=NULL)
    {
        q = p ->next;
        delete p;
        p = q;
    }
    currentLength =0;
}

template<class elemType>
void sLinkList<elemType>::insert(int i, const elemType &x)
{
    node *pos;

    pos = move(i -1 );
    pos->next=new node(x,pos->next);
    ++currentLength;
}

template<class elemType>
void sLinkList<elemType>::remove(int i)
{
    node *pos,*delp;

    pos = move(i-1);
    delp = pos->next;
    pos->next = delp ->next;
    delete delp;
    --currentLength;
}

template<class elemType>
int sLinkList<elemType>::search(const elemType&x) const
{
    node *p = head -> next;
    int i =0;

    while(p!=NULL&&p->data!=x){p=p->next;++i;}
    if(p == NULL) return -1;else return i;
}

template<class elemType>
elemType sLinkList<elemType>::visit(int i)const
{
    return move(i)->data;
}

template<class elemType>
void sLinkList<elemType>::traverse()const
{
    node *p = head ->next;
    cout << endl;
    while(p != NULL)
    {
        cout <<p->data<<" ";
        p = p->next;
    }
    cout << endl;
}

//double 

template <class elemType>
dLinkList<elemType>::dLinkList()
{
    head = new node;
    head ->next = tail = new node;
    tail ->prev = head;
    currentLength = 0;
}

template <class elemType>
typename dLinkList<elemType>::node *dLinkList<elemType>::move(int i ) const
{
    node *p = head;
    while (i-- >= 0) p =p->next;
    return p;
}

template <class elemType>
void dLinkList<elemType>::insert(int i, const elemType &x)
{
    node *pos ,*tmp;
    pos = move(i);
    tmp = new node(x,pos->prev,pos);
    pos ->prev->next = tmp;
    pos->prev = tmp;
    ++currentLength;
}

template <class elemType>
void dLinkList<elemType>::remove(int i)
{
    node *pos;

    pos= move(i);
    pos->prev->next = pos ->next;
    pos ->next ->prev = pos->prev;
    delete pos;
    --currentLength;
}

template<class elemType>
void dLinkList<elemType>::clear()
{
    node *p = head->next,*q;
    head->next = tail;
    tail->prev = head;
    while(p!=tail){
        q = p->next;
        delete p;
        p = q;
    }
    currentLength = 0;
}

template <class elemType>
int dLinkList<elemType>::search(const elemType &x)const 
{
    node *p = head->next;
    int i;
    for (i = 0; p != tail && p->data != x;++i) 
        p = p->next;
    if (p==tail)
        return -1;
    else 
        return i;
}

template <class elemType>
elemType dLinkList<elemType>::visit(int i)const
{
    return move(i)->data;
}

template <class elemType>
void dLinkList<elemType>::traverse()const
{
    node *p = head->next;
    cout << endl;
    while(p!=tail){
        cout << p->data << ' ';
        p = p->next;
    }
    cout << endl;
}
