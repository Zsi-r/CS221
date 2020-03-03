#include <iostream>
using namespace std;

template <class typeofver, class typeofedge>
class adjListGraph
{
public:
    adjListGraph(int vSize);
    void insert(typeofver x, typeofver y, typeofedge w);
    int kruskal() const;
    ~adjListGraph();

private:
    struct kruskalEdge
    {
        int beg, end;
        typeofedge w;
        bool operator<(const kruskalEdge &rp) const { return w < rp.w; }
    };
    struct edgeNode
    {
        int end;
        typeofedge weight;
        edgeNode *next;

        edgeNode(int e, typeofedge w, edgeNode *n = NULL)
        {
            end = e;
            weight = w;
            next = n;
        }
    };
    struct verNode
    {
        typeofver ver;
        edgeNode *head;

        verNode(edgeNode *h = NULL) { head = h; }
    };

    int Vers, Edges;
    verNode *verList;
    int find(typeofver v) const
    {
        for (int i = 0; i < this->Vers; i++)
            if (verList[i].ver == v)
                return i;
    }
};

template <class Type>
class priorityQueue
{
public:
    priorityQueue(int capacity = 10);
    priorityQueue(const Type data[],int size);
    ~priorityQueue();
    bool isEmpty()const;
    void enQueue(const Type &x);
    Type deQueue();
    Type getHead() const;
private:
    int currentSize;
    Type *array;//array[0]不放东西
    int maxSize;

    void doubleSpace();
    void buildHeap();//对一串数字进行有序化建堆
    void percolateDown(int hole);
};

template <class Type>
priorityQueue<Type>::priorityQueue(int capacity)
{
    array = new Type[capacity];
    maxSize = capacity;
    currentSize = 0;
}

template <class Type>
priorityQueue<Type>::~priorityQueue()
{
    delete[] array;
}

template <class Type>
bool priorityQueue<Type>::isEmpty() const
{
    return currentSize == 0;
}

template <class Type>
Type priorityQueue<Type>::getHead() const
{
    return array[1];
}

template <class Type >
void priorityQueue<Type>::enQueue(const Type &x)
{
    if (currentSize == maxSize-1)//因为array[0]不放东西
        doubleSpace();
    
    //向上过滤
    int hole = ++currentSize;
    for (; hole > 1 && x < array[hole / 2]; hole /= 2)
        array[hole] = array[hole / 2];
    array[hole] = x;
}

template <class Type >
Type priorityQueue<Type >::deQueue()
{
    Type miniItem;
    miniItem = array[1];
    array[1] = array[currentSize--];//把最大(maybe)的数放在第一个，再向下过滤
    percolateDown(1);
    return miniItem;
}

template<class Type >
void priorityQueue<Type >:: percolateDown(int hole)//向下过滤
{
    int child;
    Type tmp = array[hole];
    for (; hole * 2 <= currentSize; hole = child){
        child = hole * 2;
        if (child!=currentSize && array[child+1]<array[child])//找小的儿子，如果child==currentSize，则没有右儿子
            child++;
        if(array[child]<tmp)
            array[hole] = array[child];
        else
            break;
    }
    array[hole] = tmp;
}

template <class Type >
void priorityQueue<Type >::buildHeap()
{
    for (int i = currentSize / 2; i > 0;i--)
        percolateDown(i);
}

template <class Type>
priorityQueue<Type>::priorityQueue(const Type *items, int size) : maxSize(size + 10), currentSize(size)
{
    array = new Type[maxSize];
    for (int i = 0; i < size;i++)
        array[i + 1] = items[i];
    buildHeap();
}

template <class Type >
void priorityQueue<Type >::doubleSpace()
{
    Type *tmp = array;
    maxSize *= 2;
    array = new Type[maxSize];
    for (int i = 0; i <= currentSize; i++) //当currentSize == maxSize-1时，调用doubleSpace()
        array[i] = tmp[i];
    delete[] tmp;
}

class DisjointSet{
private:
    int size;
    int *parent;
public:
    DisjointSet(int s);
    ~DisjointSet() { delete[] parent; }
    void Union(int root1, int root2);
    int Find(int x);
};

DisjointSet::DisjointSet(int s)
{
    size = s;
    parent = new int[size];
    for (int i = 0; i < size;i++)
        parent[i] = -1;
}

int DisjointSet::Find(int x)
{
    if (parent[x]<0)
        return x;
    return parent[x] = Find(parent[x]);
}

void DisjointSet::Union(int root1,int root2)
{
    if (root1==root2)
        return;
    if (parent[root1]>parent[root2])
    {
        parent[root2] += parent[root1];
        parent[root1] = root2;
    }
    else
    {
        parent[root1] += parent[root2];
        parent[root2] = root1;
    }
}

template <class typeofver, class typeofedge>
adjListGraph<typeofver, typeofedge>::adjListGraph(int vSize)
{
    this->Vers = vSize;

    verList = new verNode[vSize];
    for (int i = 0; i < vSize;i++)
    {
        verList[i].ver = i+1;
    }
}

template<class typeofver,class typeofedge>
adjListGraph<typeofver,typeofedge>::~adjListGraph()
{
    int i;
    edgeNode *p;

    for (i = 0; i < this->Vers;i++)
        while((p=verList[i].head)!=NULL)
        {
            verList[i].head = p->next;
            delete p;
        }
    delete[] verList;
}

template <class typeofver,class typeofedge>
void adjListGraph<typeofver ,typeofedge>::insert(typeofver x,typeofver y,typeofedge w)
{
    int u = find(x), v = find(y);
    verList[u].head = new edgeNode(v, w, verList[u].head);
    ++this->Edges;
}

template<class typeofver,class typeofedge>
int adjListGraph<typeofver,typeofedge>::kruskal()const
{
    int count = 0;
    int edgesAccepted = 0, u, v;
    edgeNode *p;
    kruskalEdge e;
    DisjointSet ds(this->Vers);
    priorityQueue<kruskalEdge> pq;

    //生成优先级队列
    for (int i = 0; i < this->Vers;i++)
    {
        for (p = verList[i].head; p != NULL; p = p->next)
            if (i<p->end)
            {   
                e.beg = i;
                e.end = p->end;
                e.w = p->weight;
                pq.enQueue(e);
            }
    }

    //开始归并
    while(edgesAccepted<(this->Vers)-1)
    {
        e = pq.deQueue();
        u = ds.Find(e.beg);
        v = ds.Find(e.end);
        if(u!=v){
            edgesAccepted++;
            count += e.w;
            ds.Union(u, v);
        }
    }
    return count;
}

int main()
{
    int numofver, numofedge,weight,node1,node2,tmp;
    cin >> numofver >> numofedge;
    adjListGraph<int, int> gf(numofver);
    for (int i = 0; i < numofedge;i++)
    {
        cin >> node1 >> node2 >> weight;
        if (node1>node2){
            tmp = node2;
            node2 = node1;
            node1 = tmp;
        }
        gf.insert(node1, node2, weight);
    }
    cout << gf.kruskal() << endl;
    return 0;
}