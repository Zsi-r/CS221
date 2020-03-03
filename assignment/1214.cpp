#include <iostream>

using namespace std;
//树的后根遍历 == 二叉树的中序遍历
//树的先根遍历 == 二叉树的先序遍历

class node
{
public:
    int data = NULL;
    int lchild = 0, brother = 0;
    node() {};
    node(int d, int l, int b) : data(d), lchild(l), brother(b){};
    node(node &x) { data = x.data, lchild = x.lchild, brother = x.brother; }
    ~node(){};
};

class linkQueue
{
    private:
    struct nodeInQueue{
        node data;
        nodeInQueue *next;
        nodeInQueue (const node &x, nodeInQueue *N = NULL)
        {
            data=x;next=N;
        }
        nodeInQueue() : next(NULL) {};
        ~nodeInQueue() {};
    };

    nodeInQueue *front,*rear;//队不空时，front和rear都有数据，当队长为1时，front和rear所指相同

    public:
    linkQueue();
    ~linkQueue();
    bool isEmpty()const ;
    void enQueue(const node &x);
    node deQueue();
};

linkQueue::linkQueue()
{
    front = rear = NULL;
}

linkQueue::~linkQueue()
{
    nodeInQueue *tmp;
    while(front != NULL)
    {
        tmp = front;
        front = front ->next;
        delete tmp;
    }
}

bool linkQueue::isEmpty()const
{
    return front == NULL;
}

void linkQueue::enQueue(const node &x)
{
    if (rear == NULL) front = rear = new nodeInQueue (x);
    else 
        rear=rear->next=new nodeInQueue (x);
}

node linkQueue::deQueue()
{
    nodeInQueue *tmp=front;
    node value = front ->data;
    front = front ->next;
    if (front==NULL)rear=NULL;
    delete tmp;
    return value;
}


void pre(int accessnow,node*tree) 
{
    cout << tree[accessnow].data << " ";
    if (tree[accessnow].lchild != 0)
        pre(tree[accessnow].lchild-1, tree);
    if (tree[accessnow].brother != 0)
        pre(tree[accessnow].brother-1, tree);
    return;
}

void post(int accessnow,node*tree) 
{
    if (tree[accessnow].lchild != 0)
        post(tree[accessnow].lchild-1, tree);

    cout << tree[accessnow].data << " ";

    if (tree[accessnow].brother != 0)
        post(tree[accessnow].brother-1, tree);
    return;
}

void level(linkQueue &s,node *tree){
    node temp;
    while (!s.isEmpty()){
        temp = s.deQueue();
        if (temp.lchild!=0)
            s.enQueue(tree[temp.lchild-1]);
        cout << temp.data << ' ';
        while(temp.brother!=0){
            temp = tree[temp.brother-1];
            cout << temp.data << ' ';
            if (temp.lchild!=0)
                s.enQueue(tree[temp.lchild-1]);
        }
    }
}

int main()
{
    int NumNode;
    cin >> NumNode;
    node *tree = new node[NumNode];
    linkQueue que;

    int RootLine;
    bool *FindRoot = new bool[NumNode+1];
    for (int i = 0; i < NumNode + 1;i++)
        FindRoot[i] = false;

    for (int i = 0; i < NumNode;i++)
    {
        cin >> tree[i].lchild >> tree[i].brother >> tree[i].data;
        FindRoot[tree[i].lchild] = true;
        FindRoot[tree[i].brother] = true;
    }

    for (RootLine = 1; RootLine < NumNode + 1;RootLine ++)
    {
        if (!FindRoot[RootLine])
            break;
    }

    pre(RootLine-1, tree);
    cout << endl;
    post(RootLine-1, tree);

    que.enQueue(tree[RootLine-1]);

    cout << endl;
    level(que, tree);
    return 0;
}