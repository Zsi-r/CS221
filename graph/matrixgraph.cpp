#include "graph.h"

template <class typeofver, class typeofedge>
class adjMatrixGraph : public graph<typeofver, typeofedge>
{
public:
    adjMatrixGraph(int vSize, const typeofver d[], const typeofedge noEdgeFlag);
    void insert(typeofver x, typeofver y, typeofedge w);
    void remove(typeofver x, typeofver y);
    bool exist(typeofver x, typeofver y) const;
    ~adjMatrixGraph();

private:
    typeofedge **edge;
    typeofver *ver;
    typeofedge noEdge;
    int Maxsize;   //矩阵可容纳最大规模
    bool directed; //是否有向图
    int find(typeofver v) const
    {
        for (int i = 0; i < this->Vers; i++) //需要加this->或adjMatrixGraph<typeofver,typeofedge>::
            if (ver[i] == v)
                return i;
    }
};

template <class typeofver, class typeofedge>
adjMatrixGraph<typeofver, typeofedge>::adjMatrixGraph(int vSize, const typeofver d[], const typeofedge noEdgeFlag)
{
    int i, j;
    this->Vers = vSize;
    this->Edges = 0;
    noEdge - noEdgeFlag;

    ver = new typeofver[vSize];
    for (i = 0; i < vSize; ++i)
        ver[i] = d[i];
    edge = new typeofedge *[vSize];
    for (i = 0; i < vSize; i++)
    {
        edge[i] = new typeofedge[vSize];
        for (j = 0; j < vSize; j++)
            edge[i][j] = noEdge; //noEdge书上设置为∞
        edge[i][i] = 0;
    }
}

template <class typeofver, class typeofedge>
adjMatrixGraph<typeofver, typeofedge>::~adjMatrixGraph()
{
    delete[] ver;
    for (int i = 0; i < this->Vers; ++i)
        delete[] edge[i];
    delete[] edge;
}

template <class typeofver, class typeofedge>
void adjMatrixGraph<typeofver, typeofedge>::insert(typeofver x, typeofver y, typeofedge w)
{
    int u = find(x), v = find(y);
    edge[u][v] = w;
    ++this->Edges;
}

template <class typeofver, class typeofedge>
void adjMatrixGraph<typeofver, typeofedge>::remove(typeofver x, typeofver y)
{
    int u = find(x), v = find(y);
    edge[u][v] = noEdge;
    --this->Edges;
}

template <class typeofver, class typeofedge>
bool adjMatrixGraph<typeofver, typeofedge>::exist(typeofver x, typeofver y) const
{
    int u = find(x), v = find(y);
    if (edge[u][v] != noEdge)
        return true;
    else
        return false;
}