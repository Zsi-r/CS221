#include <iostream>
#include <queue>
using namespace std;

class graph
{
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
    verNode *verList;
    int Vers, Edges;
    int find(int v) const
    {
        for (int i = 0; i < Vers; i++)
            if (verList[i].ver == v)
                return i;
    }

public:
    graph(int vSize, int d[])
    {
        Vers = vSize;
        verList = new verNode [vSize];
        for (int i = 0; i < vSize;i++)
        {
            verList[i].ver = d[i];
        }
    }
    ~graph(){
        int i;
        edgeNode *p;
        for (i = 0; i < Vers;i++)
        {
            while((p=verList[i].head)!=NULL)
            {
                verList[i].head = p->next;
                delete p;
            }
        }
        delete[] verList;
    }
    
    void insert(int x,int y,int w=1)
    {
        int u = find(x), v = find(y);
        verList[u].head = new edgeNode(v, w, verList[u].head);
        ++Edges;
    }

    int bfs(int start)const
    {
        int max = 0;
        bool *visited = new bool[this->Vers];

        int currentNode;
        queue<int,deque<int>> q;
        edgeNode *p;

        for (int i=0;i<this->Vers;i++)
            visited[i] = false;

        q.push(start);
        while(!q.empty())
        {
            currentNode = q.front();
            q.pop();
            if (visited[currentNode]==true)continue;

            if (max<verList[currentNode].ver)
                max = verList[currentNode].ver;

            visited[currentNode] = true;
            p = verList[currentNode].head;
            while(p!=NULL)
            {
                if(visited[p->end]==false)q.push(p->end);
                p = p->next;
            }
        }
        return max;
    }

};

int main()
{
    int n, m, x, y;
    cin >> n >> m;
    int *templist = new int[n];
    for (int i = 0; i < n;i++)
    {
        templist[i] = i + 1;
    }
    graph g(n,templist);
    for (int i = 0; i < m;i++)
    {
        cin >> x >> y;
        g.insert(x, y);
    }

    for (int i = 0; i < n; i++)
    {
        cout << g.bfs(i)<<' ';
    }
    return 0;
}