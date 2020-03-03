#include <iostream>
using namespace std;

class graph
{
private:
    struct edgeNode
    {
        int end;
        edgeNode *next;
        edgeNode(int e, edgeNode *n = NULL) : end(e), next(n){};
    };

    int Vers, Edges,M;//the target to the length of path
    edgeNode **verList;

public:

    int dfs(int start, bool visited[],int currentlength) const
    {   
        int count = 0;
        edgeNode *p = verList[start];
        visited[start] = true;
        if (currentlength==M)
            return 1;
        while (p != NULL)
        {
            if (visited[p->end] == false)
            {
                count+= dfs(p->end, visited,currentlength+1);
                visited[p->end] = false;
            }
            p = p->next;
        }
        return count;
    }
/*
    int dfs(int start,bool visited[],int currentlength)
    {

    }
*/
public:
    graph(int vSize, int eSize,int Mtmp)
    {
        Vers = vSize;
        Edges = eSize;
        M = Mtmp;
        verList = new edgeNode*[vSize+1];
        for (int i = 0; i <= vSize; i++)
            verList[i] = NULL;
    }
    ~graph()
    {
        edgeNode *p;
        for (int i = 1; i <= Vers; i++)
        {
            p = verList[i];
            while (p != NULL)
            {
                verList[i] = p->next;
                delete p;
                p = verList[i];
            }
        }
        delete[] verList;
    }
    void insert(int x, int y)
    {
        verList[x]= new edgeNode(y, verList[x]);
    }
    
};

int main()
{
    int numofver, numofedge, startnode, goal,nodeofedge1,nodeofedge2;
    cin >> numofver >> numofedge >> startnode >> goal;
    graph gf(numofver, numofedge, goal);
    for (int i = 0; i < numofedge;i++)
    {
        cin >> nodeofedge1 >> nodeofedge2;
        gf.insert(nodeofedge1, nodeofedge2);
    }
    bool *visited = new bool[numofver+1];
    for (int i = 0; i <= numofver;i++)
        visited[i] = false;
    cout << gf.dfs(startnode, visited, 0)<<endl;
}