#include <iostream>
#include <cstring>

using namespace std;

class myqueue
{
    private:
        struct node
        {
            int data;
            node *next;

            node(int x, node *N=NULL){
                data = x; next = N;
            }
            node ():next(NULL){};
            ~node(){};
        };

        node *front,*rear;

        node * move(int i) const;

    public:
        myqueue();
        ~myqueue() ;
        void enqueue(int x);
        int dequeue();
        int getHead()const;
        void sort(int x);
        void traverse()const ;
};

myqueue::myqueue()
{
    front = rear = NULL;
}

myqueue::~myqueue()
{
    node *tmp;
    while(front != NULL)
    {
        tmp = front;
        front = front ->next;
        delete tmp;
    }
}

int myqueue::getHead() const
{
    return front->data;
}

int myqueue::dequeue()
{
    node *tmp=front;
    int value = front->data;
    front= front->next;
    if(front==NULL)rear=NULL;
    delete tmp;
    return value;
}

void myqueue::sort(int x)
{
    if (rear ==NULL)front = rear = new node (x);
    else
    {
        node *p=front,*q=NULL,*tmp;
        while(p!=NULL&&(p->data<x))//p==NULL时,若不分类讨论，p->data会报错，且p!=NULL要放在前面
        {
            q=p;
            p=p->next;
        }
        if (q==NULL)//即应插在队头
        {
            front = tmp = new node(x,p);
        }
        else if (p==NULL)//即应插在队尾
        {
            rear=tmp=new node(x);
            q->next = tmp;
        }
        else {//插在中间
          tmp = new node(x, p);
          q->next = tmp;
        }
    }
}

void myqueue::enqueue(int x)
{
    if (rear ==NULL)front = rear = new node (x);
    else
        rear=rear->next=new node (x);
}

void myqueue::traverse()const
{
    node *p = front;
    while(p!=NULL)
    {
        cout << p->data<<endl;
        p=p->next;
    }
}

int main()
{
    int M;
    int NUM;
    char movement[10];
    myqueue intqueue;
    myqueue output;

    cin >> M;
    for (int i=0;i<M;++i)
    {
        cin >> movement;
        switch(movement[0]){
            case 'i':
                    cin >> NUM;
                    intqueue.sort(NUM);
                    break;
            case 'd':
                    intqueue.dequeue() ;
                    break;
            case 'm':
                    output.enqueue(intqueue.getHead()) ;
                    break;
        }
    }

    output.traverse();

    return 0;
}
