#include <iostream>

using namespace std;

struct node
{
    int leftchild, rightchild;
    node() : leftchild(-1), rightchild(-1){};
    bool haveonlyleftchild()
    {
        return leftchild >= 0 && rightchild == -1;
    }
    bool haveonlyrightchild()
    {
        return leftchild == -1 && rightchild >= 0;
    }
    bool havenochild()
    {
        return leftchild == -1 && rightchild == -1;
    }
    bool havebothchild()
    {
        return leftchild >= 0 && rightchild >= 0;
    }
};

class que
{
    struct n
    {
        node data;
        n *next;
        n(const node &x,n*n = NULL)
        {
            data = x;
            next = n;
        }
        n():next(NULL){}
        ~n(){}
    };

    n *front, *rear;
public:
    que() { front = rear = NULL; }
    bool isempty()
    {
        return front == NULL;
    }
    ~que() {
        n *temp;
        while(front!=NULL)
        {
            temp = front;
            front = front->next;
            delete temp;
        }
    }
    void enqueue(const node &x)
    {
        if (rear==NULL)
            front = rear = new n(x);
        else 
        {
            rear->next = new n(x);
            rear = rear->next;
        }
    }
    node dequeue()
    {
        n *temp = front;
        node value = front->data;
        front = front->next;
        if (front ==NULL)
            rear = NULL;
        delete temp;
        return value;
    }

};

class tree
{
    friend istream & operator>>(istream &is,tree &obj)
    {
        int temp;
        for (int i = 1; i < obj.len;i++)
        {
            cin >> temp;
            if (obj.list[temp].havenochild())
                obj.list[temp].leftchild = i;
            else if (obj.list[temp].haveonlyleftchild())
                obj.list[temp].rightchild = i;
        }
        return is;
    }
private:
    node *list;
    int len;
    bool iscbt(int n)
    {
        que q;
        if (list[n].havenochild())
            return true;
        bool flag = false;
        q.enqueue(list[n]);
        while(!q.isempty())
        {
            node temp = q.dequeue();
            if (temp.haveonlyrightchild())
                return false;
            if (!flag){
                if (temp.havebothchild())
                {
                    q.enqueue(list[temp.leftchild]);
                    q.enqueue(list[temp.rightchild]);
                    continue;
                }
                else if (temp.haveonlyleftchild())
                {
                    q.enqueue(list[temp.leftchild]);
                    flag = true;
                    continue;
                }
                else if (temp.havenochild())
                {
                    flag = true;
                    continue;
                }
            }
            else{
                if (!temp.havenochild())
                    return false;
            }
        }
        return true;
    }
public:
    tree(int n){
        list = new node[n];
        len = n;
    }
    bool iscbt()
    {
        return iscbt(0);
    }
};

int main()
{
    int n;
    cin >> n;
    tree t(n);
    cin >> t;
    bool flag = t.iscbt();
    if (flag)
        cout << "true" << endl;
    else
        cout << "false" << endl;
    return 0;
}