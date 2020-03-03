#include <iostream>
#include <cstring>

using namespace std;

template <class elemType>
class sLinkList
{
public:
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

    sLinkList();
    ~sLinkList(){clear();delete head;}

    void clear();
    int length()const {return currentLength;}
    void insert(int i,const elemType &x);
    elemType visit(int i) const;
    void traverse()const;
};

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

    pos = move(i -1);
    pos->next=new node(x,pos->next);
    ++currentLength;
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
    while(p != NULL)
    {
        cout <<p->data;
        p = p->next;
    }
}


int main()
{
    char *l1=new char[1000001];
    char *l2=new char[1000001];
    char *resultstring=new char[1000002];
    cin >> l1>>l2;

    int i=0,j=0,len3=0,quotient,rem=0,temp,k=0,len1=strlen(l1),len2=strlen(l2);

    sLinkList<char> list1,list2,list3;
    while(i<len1)
    {
        list1.insert(0,l1[i]);
        i++;
    }

    while(j<len2)
    {
        list2.insert(0,l2[j]);
        j++;
    }

    sLinkList<char>::node *p=list1.head->next,*q=list2.head->next;

    while(len3<i&&len3<j)
    {
        temp = (p->data)+(q->data)-'0'-'0'+rem;
        quotient = temp%10;
        list3.insert(0,quotient+'0');
        rem = temp/10;
        len3++;
        p=p->next;q=q->next;
    }

    while(len3<i)
    {
        temp = (p->data)-'0'+rem;
        quotient = temp%10;
        list3.insert(0,quotient+'0');
        rem = temp/10;
        len3++;
        p=p->next;
    }

    while(len3<j)
    {
        temp = (q->data)-'0'+rem;
        quotient = temp%10;
        list3.insert(0,quotient+'0');
        rem = temp/10;
        len3++;
        q = q->next;
    }

    if (rem!=0){list3.insert(0,rem+'0');len3++;}
    p=list3.head->next;
    for (k=0;k<len3;k++){resultstring[k]=p->data;p=p->next;}
    cout<<resultstring;

    return 0;
}
