#include <iostream>

using namespace std;

//single

class sLinkList
{
private:
    struct node
    {
        int data;
        node *next;

        node(const int &x, node *N=NULL){
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
    ~sLinkList(){delete head;}

    int length()const {return currentLength;}
    void insert(int i,int x);
    int eat(int N, int M);
};

typename sLinkList::node *sLinkList::move(int i)const
{
    node *p = head;
    while(i-->=0)p = p->next;
    return p;
}

sLinkList::sLinkList()
{
    head = new node;
    currentLength = 0;
}


void sLinkList::insert(int i,int x)
{
    node *pos;

    pos = move(i -1 );
    pos->next=new node(x,pos->next);
    ++currentLength;
}



int sLinkList::eat(int N, int M)
{
    node *p = head->next, *tmp;
    int length = N;

    tmp = move(N - 1);
    tmp->next = head->next;

    node *q = tmp ;

    while(length!=1)
    {   
        if (M > 1)
        {   
            for (int i = 0; i < M-1;i++)
            {
                q = p;
                p = p->next;
            }
        }
        q->next = p->next;
        delete p;
        length--;
        p = q->next;
    }
    head->next = p;
    return p->data;
}

int main()
{
    int N, M;
    cin >> N >> M;

    sLinkList mylist;

    for (int i = 0; i < N;i++)
    {
        mylist.insert(i, i + 1);
    }
    cout << mylist.eat(N, M);
}