#include <iostream>
#include <queue>

using namespace std;

struct sdNode //short distance node
{
    int end;
    int distance;
    int prev;
    int count;
    sdNode(){};
    sdNode(int e, int d, int p, int c) : end(e), distance(d), prev(p), count(c){};
};

class priorityQueue
{
public:
    priorityQueue(int capacity = 5);
    ~priorityQueue();
    bool isEmpty() const;
    void enQueue(int end, int distance, int prev, int count);
    sdNode deQueue();

private:
    int currentSize;
    sdNode *array; //array[0]不放东西
    int maxSize;

    void doubleSpace();
    void buildHeap(); //对一串数字进行有序化建堆
    void percolateDown(int hole);
};

priorityQueue::priorityQueue(int capacity)
{
    array = new sdNode[capacity];
    maxSize = capacity;
    currentSize = 0;
}

priorityQueue::~priorityQueue()
{
    delete[] array;
}

bool priorityQueue::isEmpty() const
{
    return currentSize == 0;
}

void priorityQueue::enQueue(int end, int distance, int prev, int count)
{
    if (currentSize == maxSize - 1) //因为array[0]不放东西
        doubleSpace();

    sdNode temp(end, distance, prev, count);
    //向上过滤
    int hole = ++currentSize;
    for (; hole > 1 && (distance < array[hole / 2].distance || (distance == array[hole / 2].distance && count < array[hole / 2].count)); hole /= 2)
        array[hole] = array[hole / 2];
    array[hole] = temp;
}

sdNode priorityQueue::deQueue()
{
    sdNode miniItem;
    miniItem = array[1];
    array[1] = array[currentSize--]; //把最大(maybe)的数放在第一个，再向下过滤
    percolateDown(1);
    return miniItem;
}

void priorityQueue::percolateDown(int hole) //向下过滤
{
    int child;
    sdNode tmp = array[hole];
    for (; hole * 2 <= currentSize; hole = child)
    {
        child = hole * 2;
        if (child != currentSize && (array[child + 1].distance < array[child].distance || (array[child + 1].distance == array[child].distance && array[child + 1].count < array[child].count))) //找小的儿子，如果child==currentSize，则没有右儿子
            child++;
        if (array[child].distance < tmp.distance || (array[child].distance == tmp.distance && array[child].count < tmp.count))
            array[hole] = array[child];
        else
            break;
    }
    array[hole] = tmp;
}

void priorityQueue::doubleSpace()
{
    sdNode *tmp = array;
    maxSize *= 2;
    array = new sdNode[maxSize];
    for (int i = 0; i <= currentSize; i++) //当currentSize == maxSize-1时，调用doubleSpace()
        array[i] = tmp[i];
    delete[] tmp;
}

class adjListGraph
{
public:
    adjListGraph(int vSize, const int d[]);
    void insert(int x, int y, int w);
    void dijkstra(int start, int end) const;
    ~adjListGraph();

private:
    struct edgeNode
    {
        int end;
        int weight;
        edgeNode *next;

        edgeNode(int e, int w, edgeNode *n = NULL)
        {
            end = e;
            weight = w;
            next = n;
        }
    };
    struct verNode
    {
        int ver;
        edgeNode *head;

        verNode(edgeNode *h = NULL) { head = h; }
    };

    int Vers, Edges;
    verNode *verList;

    void printPath(int start, int end, int prev[]) const;
};

adjListGraph::adjListGraph(int vSize, const int d[])
{
    this->Vers = vSize;

    verList = new verNode[vSize];
    for (int i = 0; i < vSize; i++)
    {
        verList[i].ver = d[i];
    }
}

adjListGraph::~adjListGraph()
{
    int i;
    edgeNode *p;

    for (i = 0; i < this->Vers; i++)
        while ((p = verList[i].head) != NULL)
        {
            verList[i].head = p->next;
            delete p;
        }
    delete[] verList;
}

void adjListGraph::insert(int x, int y, int w)
{
    int u = x - 1, v = y - 1;
    verList[u].head = new edgeNode(v, w, verList[u].head);
    ++this->Edges;
}

void adjListGraph::printPath(int start, int end, int prev[]) const
{
    if (start == end)
    {
        cout << verList[start].ver;
        return;
    }
    printPath(start, prev[end], prev);
    cout << ' ' << verList[end].ver;
}

void adjListGraph::dijkstra(int start, int end) const
{
    int *prev = new int[this->Vers];
    bool *known = new bool[this->Vers];

    int sNo, i, dis;
    edgeNode *p;
    sdNode temp;

    for (i = 0; i < this->Vers; i++)
    {
        known[i] = false;
    }

    sNo = start - 1;

    priorityQueue que;
    que.enQueue(sNo, 0, sNo, 1);
    prev[sNo] = sNo;

    while (!que.isEmpty())
    {
        temp = que.deQueue();

        if (known[temp.end])
            continue;

        known[temp.end] = true;
        prev[temp.end] = temp.prev;

        if (temp.end == end - 1)
            break;

        for (p = verList[temp.end].head; p != NULL; p = p->next)
            if (!known[p->end])
            {
                dis = temp.distance + p->weight;
                que.enQueue(p->end, dis, temp.end, temp.count+1);
            }
    }

    cout << temp.distance << endl;
    printPath(sNo, end - 1, prev);
}

int main()
{
    int n, m, start, end, edgestart, edgeend, edgeweight;

    cin >> n >> m >> start >> end;

    int *verarray = new int[n];
    for (int i = 0; i < n; i++)
    {
        verarray[i] = i + 1;
    }
    adjListGraph graph(n, verarray);
    for (int i = 0; i < m; i++)
    {
        cin >> edgestart >> edgeend >> edgeweight;
        graph.insert(edgestart, edgeend, edgeweight);
    }
    graph.dijkstra(start, end);
    return 0;
}