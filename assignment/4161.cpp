#include <iostream>
#include <cstring>
//以1，2，3，4进栈，之后比它大的数要从小到大排
using namespace std;

class seqStack
{
    private:
        int *elem;
        int top_p;
        int maxSize;
        void doubleSpace();
    public:
        seqStack(int initSize = 10);
        ~seqStack();
        bool isEmpty() const;
        void push(int x);
        int pop();
        int top() const;
};

seqStack::seqStack(int initSize)
{
    elem = new int[initSize];
    maxSize = initSize;
    top_p = -1;
}

seqStack::~seqStack()
{
    delete []elem;
}


bool seqStack::isEmpty() const
{
    return top_p==-1;
}


void seqStack::push(int x)
{
    if (top_p==maxSize-1) doubleSpace();
    elem[++top_p] = x;
}


int seqStack::pop()
{
    return elem[top_p--];
}


int seqStack::top() const
{
    return elem[top_p];
}


void seqStack::doubleSpace()
{
    int
 *tmp = elem;

    elem  = new int [2*maxSize];

    for (int i =0;i<maxSize ; i++)
    {
        elem[i]= tmp[i];
    }
    maxSize *=2;
    delete []tmp;
}

int main()
{   
    int Num_of_cars;
    int *cars;
    int count = 1;
    seqStack stage_C;
    cin >> Num_of_cars;

    cars = new int[Num_of_cars];
    for (int i = 0; i < Num_of_cars;++i)
    {
        cin >> cars[i];
    }

    for (int j = 0; j < Num_of_cars;++j)
    {
        while(count != Num_of_cars && (stage_C.isEmpty() || stage_C.top()!=cars[j]))
        {
            stage_C.push(count);
            count++;
        }
        if(stage_C.top()==cars[j])
        {
            stage_C.pop();
            continue;
        }
    }

    if (stage_C.isEmpty())
    {
        cout << "Yes" << endl;
    }
    else
        cout << "No" << endl;

    return 0;
}