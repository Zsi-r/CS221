#include "disjointset.cpp"
#include "graph.h"
#include "linkQueue.cpp"
#include "priorityQueue.cpp"

template <class typeofver, class typeofedge>
class adjListGraph : public graph<typeofver, typeofedge>
{
public:
    adjListGraph(int vSize, const typeofver d[]);
    void insert(typeofver x, typeofver y, typeofedge w);
    void remove(typeofver x, typeofver y);
    bool exist(typeofver x, typeofver y) const;
    void dfs() const;
    void bfs() const;
    void EulerCircuit(typeofver start);
    void kruskal() const;
    void prim(typeofedge noEdge) const;
    void unweightedShortDistance(typeofver start, typeofedge noEdge) const;
    void dijkstra(typeofver start, typeofedge noEdge) const;
    void floyd() const;
    ~adjListGraph();

private:
    struct kruskalEdge
    {
        int beg, end;
        typeofedge w;
        bool operator<(const kruskalEdge &rp) const { return w < rp.w; }
    };
    struct EulerNode
    {
        int NodeNum;
        EulerNode *next;
        EulerNode(int ver)
        {
            NodeNum = ver;
            next = NULL;
        }
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

    verNode *verList;
    int find(typeofver v) const
    {
        for (int i = 0; i < this->Vers; i++)
            if (verList[i].ver == v)
                return i;
    }
    void dfs(int start, bool visit[]) const;
    void EulerCircuit(int start, EulerNode *&beg, EulerNode *&end);
    verNode *clone() const;
    void printPath(int start, int end, int prev[]) const;
};

template <class typeofver, class typeofedge>
adjListGraph<typeofver, typeofedge>::adjListGraph(int vSize, const typeofver d[])
{
    this->Vers = vSize;

    verList = new verNode[vSize];
    for (int i = 0; i < vSize; i++)
    {
        verList[i].ver = d[i];
    }
}

template <class typeofver, class typeofedge>
adjListGraph<typeofver, typeofedge>::~adjListGraph()
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

template <class typeofver, class typeofedge>
void adjListGraph<typeofver, typeofedge>::insert(typeofver x, typeofver y, typeofedge w)
{
    int u = find(x), v = find(y);
    verList[u].head = new edgeNode(v, w, verList[u].head);
    ++this->Edges;
}

template <class typeofver, class typeofedge>
void adjListGraph<typeofver, typeofedge>::remove(typeofver x, typeofver y)
{
    int u = find(x), v = find(y);
    edgeNode *p = verList[u].head, *q;

    if (p == NULL)
        return;

    if (p->end == v)
    {
        verList[u].head = p->next;
        delete p;
        --this->Edges;
        return;
    }

    while (p->next != NULL && p->next->end != v)
        p = p->next;
    if (p->next != NULL)
    {
        q = p->next;
        p->next = q->next;
        delete q;
        --this->Edges;
    }
}

template <class typeofver, class typeofedge>
bool adjListGraph<typeofver, typeofedge>::exist(typeofver x, typeofver y) const
{
    int u = find(x), v = find(y);
    edgeNode *p = verList[u].head;

    while (p != NULL && p->end != v)
        p = p->next;
    if (p == NULL)
        return false;
    else
        return true;
}

//深度优先搜索
template <class typeofver, class typeofedge>
void adjListGraph<typeofver, typeofedge>::dfs() const
{
    bool *visited = new bool[this->Vers];

    for (int i = 0; i < this->Vers; i++)
        visited[i] = false;

    for (int i = 0; i < this->Vers; i++)
    {
        if (visited[i] == true)
            continue;
        dfs(i, visited);
        cout << endl;
    }
}

template <class typeofver, class typeofedge>
void adjListGraph<typeofver, typeofedge>::dfs(int start, bool visited[]) const
{
    edgeNode *p = verList[start].head;

    cout << verList[start].ver << '\t';
    visited[start] = true;

    while (p != NULL)
    {
        if (visited[p->end] == false)
            dfs(p->end, visited);
        p = p->next;
    }
}

//广度优先搜索
template <class typeofver, class typeofedge>
void adjListGraph<typeofver, typeofedge>::bfs() const
{
    bool *visited = new bool[this->Vers];

    int currentNode;
    linkQueue<int> q;
    edgeNode *p;

    for (int i = 0; i < this->Vers; i++)
        visited[i] = false;
    cout << "当前的广度优先遍历为" << endl;

    for (int i = 0; i < this->Vers; i++)
    {
        if (visited[i] == true)
            continue;
        q.enQueue(i);
        while (!q.isEmpty())
        {
            currentNode = q.deQueue();
            if (visited[currentNode] == true)
                continue;
            cout << verList[currentNode].ver << '\t';
            visited[currentNode] = true;
            p = verList[currentNode].head;
            while (p != NULL)
            {
                if (visited[p->end] == false)
                    q.enQueue(p->end);
                p = p->next;
            }
        }
        cout << endl;
    }
}

//欧拉回路
template <class typeofver, class typeofedge>
void adjListGraph<typeofver, typeofedge>::EulerCircuit(typeofver start)
{
    EulerNode *beg, *end, *q, *p, *tb, *te;
    int numofDegree;
    edgeNode *r;
    verNode *tmp;

    if (this->Edge == 0)
    {
        cout << "There is no EulerCircuit." << endl;
        return;
    }
    for (int i = 0; i < this->Vers; i++)
    {
        numofDegree = 0;
        r = verList[i].head;
        while (r != NULL)
        {
            numofDegree++;
            r = r->next;
        }
        if (numofDegree % 2 == 1)
        {
            cout << "There is no EulerCircuit." << endl;
            return;
        }
    }

    int i = find(start);

    tmp = clone(start);

    EulerCircuit(i, beg, end);

    while (true)
    {
        p = beg;
        while (p->next != NULL)
        {
            if (verList[p->next->NodeNum].head != NULL)
                break;
            else
                p = p->next;
        }
        if (p->next == NULL)
            break;
        q = p->next;
        EulerCircuit(q->NodeNum, tb, te);
        te->next = q->next;
        p->next = tb;
        delete q;
    }

    delete[] verList;
    verList = tmp;
    cout << "EulerCircuit is :" << endl;
    while (beg != NULL)
    {
        cout << verList[beg->NodeNum].ver << '\t';
        p = beg;
        beg = beg->next;
        delete p;
    }
    cout << endl;
}

template <class typeofver, class typeofedge>
typename adjListGraph<typeofver, typeofedge>::verNode *adjListGraph<typeofver, typeofedge>::clone() const
{
    verNode *tmp = new verNode[this->Vers];
    edgeNode *p;

    for (int i = 0; i < this->Vers; i++)
    {
        tmp[i].ver = verList[i].ver;
        p = verList[i].head;
        while (p != NULL)
        {
            tmp[i].head = new edgeNode(p->end, p->weight, tmp[i].head);
            p = p->next;
        }
    }
    return tmp;
}

template <class typeofver, class typeofedge>
void adjListGraph<typeofver, typeofedge>::EulerCircuit(int start, EulerNode *&beg, EulerNode *&end)
{
    int nextNode;

    beg = end = new EulerNode(start);
    while (verList[start].head != NULL)
    {
        nextNode = verList[start].head->end;
        remove(start, nextNode);
        remove(nextNode, start);
        start = nextNode;
        end->next = new EulerNode(start);
        end = end->next;
    }
}

//kruskal
template <class typeofver, class typeofedge>
void adjListGraph<typeofver, typeofedge>::kruskal() const
{
    int edgesAccepted = 0, u, v;
    edgeNode *p;
    kruskalEdge e;
    DisjointSet ds(this->Vers);
    priorityQueue<kruskalEdge> pq;

    //生成优先级队列
    for (int i = 0; i < this->Vers; i++)
    {
        for (p = verList[i].head; p != NULL; p = p->next)
            if (i < p->end)
            {
                e.beg = i;
                e.end = p->end;
                e.w = p->weight;
                pq.enQueue(e);
            }
    }

    //开始归并
    while (edgesAccepted < (this->Vers) - 1)
    {
        e = pq.deQueue();
        u = ds.Find(e.beg);
        v = ds.Find(e.end);
        if (u != v)
        {
            edgesAccepted++;
            ds.Union(u, v);
            cout << '(' << verList[e.beg].ver << ',' << verList[e.end].ver << ")\t";
        }
    }
}

//prim
template <class typeofver, class typeofedge>
void adjListGraph<typeofver, typeofedge>::prim(typeofedge noEdge) const
{
    bool *flag = new bool[this->Vers];
    typeofedge *lowCost = new typeofedge[this->Vers];
    int *startNode = new int[this->Vers];

    edgeNode *p;
    typeofedge min;
    int start, i, j;

    for (int i = 0; i < this->Vers; i++)
    {
        flag[i] = false;
        lowCost[i] = noEdge;
    }

    start = 0;
    for (int i = 1; i < this->Vers; i++)
    {
        for (p = verList[start].head; p != NULL; p = p->next)
            if (!flag[p->end] && lowCost[p->end] > p->weight)
            {
                lowCost[p->end] = p->weight;
                startNode[p->end] = start;
            }
        flag[start] = true;

        min = noEdge;
        for (j = 0; j < this->Vers; j++)
            if (lowCost[i] < min)
            {
                min = lowCost[j];
                start = j;
            }
        cout << '(' << verList[startNode[start]].ver << ',' << verList[start].ver << ")\t";
        lowCost[start] = noEdge;
    }
    delete[] flag;
    delete[] startNode;
    delete[] lowCost;
}

template <class typeofver, class typeofedge>
void adjListGraph<typeofver, typeofedge>::unweightedShortDistance(typeofver start, typeofedge noEdge) const
{
    linkQueue<int> q;
    typeofedge *distance = new typeofedge[this->Vers];
    int *prev = new int[this->Vers];
    int u, sNo;
    edgeNode *p;

    for (int i = 0; i < this->Vers; i++)
        distance[i] = noEdge;
    sNo = find(start);
    distance[sNo] = 0;
    prev[sNo] = sNo;
    q.enQueue(sNo);

    while (!q.isEmpty())
    {
        u = q.deQueue();
        for (p = verList[u].head; p != NULL; p = p->next)
        {
            if (distance[p->end] == noEdge)
            {
                distance[p->end] = distance[u] + 1;
                prev[p->end] = u;
                q.enQueue(p->end);
            }
        }
    }

    for (int i = 0; i < this->Vers; i++)
    {
        cout << "Path from " << start << " to " << verList[i].ver << " is " << endl;
        printPath(sNo, i, prev);
        cout << endl;
    }
}

template <class typeofver, class typeofedge>
void adjListGraph<typeofver, typeofedge>::printPath(int start, int end, int prev[]) const
{
    if (start == end)
    {
        cout << verList[start].ver;
        return;
    }
    printPath(start, prev[end], prev);
    cout << '-' << verList[end].ver;
}

template <class typeofver, class typeofedge>
void adjListGraph<typeofver, typeofedge>::dijkstra(typeofver start, typeofedge noEdge) const
{
    typeofedge *distance = new typeofedge[this->Vers];
    int *prev = new int[this->Vers];
    bool *known = new bool[this->Vers];

    int u, sNo, i, j;
    edgeNode *p;
    typeofedge min;
    for (i = 0; i < this->Vers; i++)
    {
        known[i] = false;
        distance[i] = noEdge;
    }

    sNo = find(start);

    distance[sNo] = 0;
    prev[sNo] = sNo;

    for (i = 0; i < this->Vers; i++)
    {
        min = noEdge;
        for (j = 0; j < this->Vers; j++)
        {
            if (!known[j] && distance[j] < min)
            {
                min = distance[j];
                u = j;
            }
        }
        known[u] = true;
        for (p = verList[u].head; p != NULL; p = p->next)
            if (!known[p->end] && distance[p->end] > min + p->weight)
            {
                distance[p->end] = min + p->weight;
                prev[p->end] = u;
            }
    }

    for (i = 0; i < this->Vers; i++)
    {
        cout << "Path from " << start << " to " << verList[i].ver << " is " << endl;
        printPath(sNo, i, prev);
        cout << "\t The length is " << distance[i] << endl;
    }
}

template <class typeofver, class typeofedge>
void adjListGraph<typeofver, typeofedge>::floyd() const
{
    typeofedge **d = new typeofedge *[this->Vers];
    int **prev = new int *[this->Vers];
    int i, j, k;

    for (i = 0; i < this->Vers; i++)
    {
        d[i] = new typeofedge[this->Vers];
        prev[i] = new int[this->Vers];
        for (j = 0; j < this->Vers; j++)
        {
            d[i][j] = this->edge[i][j];
            prev[i][j] = (this->edge[i][j] != this->noEdge) ? i : -1;
        }
    }

    for (k = 0; k < this->Vers; k++)
        for (i = 0; i < this->Vers; i++)
            for (j = 0; j < this->Vers; j++)
            {
                if (d[i][k] + d[k][j] < d[i][j])
                {
                    d[i][j] = d[i][k] + d[k][j];
                    prev[i][j] = prev[k][j];
                }
            }

    cout << "The shortest path is : " << endl;
    for (i = 0; i < this->Vers; i++)
    {
        cout << endl;
        for (j = 0; j < this->Vers; j++)
            cout << prev[i][j] << '\t';
    }
}