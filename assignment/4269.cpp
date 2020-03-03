#include <iostream>
#include <cstring>

using namespace std;


class seqStack
{
private:
    char *elem;
    int top_p;
    int maxSize;
    void doubleSpace();
public:
    seqStack(int initSize = 10);
    seqStack(const seqStack &s1);
    ~seqStack();
    bool isEmpty() const;
    void push(const char &x);
    char pop();
    char top() const;
    int rout(int count,char *s[]);
    void print() const;
};

seqStack::seqStack(int initSize)
{
    elem = new char[initSize];
    maxSize = initSize;
    top_p = -1;
}

seqStack::seqStack(const seqStack &s1)
{
    elem = new char[10];
    maxSize = s1.maxSize;
    top_p = s1.top_p;
    for (int i = 0; i < s1.top_p;i++)
    {
        elem[i]=s1.elem[i];
    }
}

seqStack::~seqStack()
{
    delete []elem;
}

bool seqStack::isEmpty() const
{
    return top_p==-1;
}

void seqStack::push(const char &x)
{
    if (top_p==maxSize-1) doubleSpace();
    elem[++top_p] = x;
}

char seqStack::pop()
{
    return elem[top_p--];
}

char seqStack::top() const
{
    return elem[top_p];
}

void seqStack::doubleSpace()
{
    char *tmp = elem;

    elem  = new char[2*maxSize];

    for (int i =0;i<maxSize ; i++)
    {
        elem[i]= tmp[i];
    }
    maxSize *=2;
    delete []tmp;
}

int seqStack::rout(int count,char *s[])
{
    seqStack s2,tmp;
    s[count-1] = new char[(this->top_p)+2];
    for (int i = 0; i <= top_p;i++)
    {
        s[count - 1][i] = elem[i];
    }

    bool flag = true;
    for (int i = 0; i <= top_p;i++)
    {
        tmp.push(this->elem[i]);
    }
    while (!tmp.isEmpty())
    {
        s2.push(tmp.pop());
    }
    for (int i = 0; i <= this->top_p;i++)
    {
        if (this->elem[i]!=s2.elem[i])
        {
            flag = false;
            break;
        }
    }

    if (flag)
    {
        return count;
    }
    else
    {
        seqStack s3,s4;
        int carry = 0;
        int sum;
        int x1 = top_p + 1;
        for (int i = 0; i < x1;i++)
        {
            sum = (pop()) + (s2.pop()) - '0' - '0'+carry;
            carry = sum / 10;
            s3.push(sum % 10 + '0');
        }
        if (carry !=0)
            s3.push('1');
        int x2 = s3.top_p + 1;
        for (int i = 0; i < x2;i++)
        {
            s4.push(s3.pop());
        }
        return s4.rout(count + 1, s);
    }
}

void seqStack::print()const
{
    for (int i = 0; i <= this->top_p;i++)
    {
        cout << elem[i];
    }
}

int main()
{
    char num[100];
    cin >> num;
    int count = 1;

    seqStack s1;
    char *s[20];

    for (int i = 0; i < strlen(num);i++)
    {
        s1.push(num[i]);
    }

    count = s1.rout(count,s);

    cout << count-1 << endl;

    cout << s[0];

    if (count>1){
        for (int i = 1; i < count;i++)
        {
            cout << "--->"<< s[i];
        }
    }

}