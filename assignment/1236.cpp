#include <iostream>
#include <queue>
using namespace std;

class adjListGraph
{
public:
    adjListGraph(int vSize, const int d[]);
    void insert(int x, int y, int w);
    void spfa(int start, int end) const;
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

void adjListGraph::spfa(int start ,int end) const
{
    int *distance = new int[Vers];
    int *prev = new int[Vers];
    queue<verNode> que;
    bool *inQue = new bool [Vers];

    int sNo,i;
    edgeNode *p;
    verNode v;

    for (i =0;i<Vers;i++){
        distance[i] = 1e5+5;
        inQue[i] = false;
    }

    sNo = start-1;
    distance[sNo] = 0;
    que.push(verList[sNo]);
    inQue[sNo] = true;

    while(!que.empty()){
        v = que.front();
        que.pop();
        inQue[v.ver-1] = false;
        for (p = verList[v.ver-1].head;p!=NULL;p = p->next){
            if (distance[v.ver-1]+p->weight < distance[p->end]){
                distance[p->end] = distance[v.ver-1] + p->weight;
                prev[p->end] = v.ver-1;
                if (!inQue[p->end])
                    que.push(verList[p->end]);
            }
        }
    }

    cout << distance[end-1]<<endl;
    //printPath(start-1, end, prev);
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
    graph.spfa(start, end);
    return 0;
}
