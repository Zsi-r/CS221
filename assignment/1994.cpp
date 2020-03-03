#include <iostream>

using namespace std;

class DisjointSet{
private:
    int size;
    int *parent;
public:
    DisjointSet(int s);
    ~DisjointSet() { delete[] parent; }
    void Union(int root1, int root2);
    int Find(int x);
    void isOne(int x);
    int countCountry();
    void print();
};

void DisjointSet::print()
{
    for (int i = 0; i < size;i++)
        cout << parent[i] << ' ';
    cout << endl;
}

int DisjointSet::countCountry()
{
    int count = 0;
    for (int i = 0; i < size;i++)
    {
        if (parent[i] < 0)
            count++;
    }
    return count;
}

void DisjointSet::isOne(int x)
{
    parent[x] = 0;
}

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

int main()
{
    int m, n;
    cin >> n >> m;
    int **array = new int *[n];
    for (int i = 0; i < n;i++)
    {
        array[i] = new int[m];
        for (int j = 0; j < m;j++)
        {
            cin >> array[i][j];
        }
    }

    //输入的第一行
    DisjointSet djs(n * m);
    if(array[0][0]==-1)
        djs.isOne(0);

    for (int i = 1; i < m; i++)
    {
        if (array[0][i] == -1)
            djs.isOne(i);
        else
            if (array[0][i-1]==0)
                djs.Union(djs.Find(i), djs.Find(i - 1));        
    }


    //接下来的n-1行
    for (int i = 1; i < n; i++)
    {
        if (array[i][0]==-1)
            djs.isOne(i* m);
        else 
            if (array[i-1][0]==0)
            djs.Union(djs.Find((i - 1) * m), djs.Find(i * m));
    }


    for (int i = 1; i < n; i++)
    {
        for (int j = 1; j < m; j++)
        {
            if (array[i][j]==-1)
                djs.isOne(i * m + j);
            else 
            {
                if (array[i][j-1]==0)
                    djs.Union(djs.Find(i * m + j - 1), djs.Find(i * m + j));
                if (array[i-1][j]==0)
                    djs.Union(djs.Find(i * m - m + j), djs.Find(i * m + j));
            }
        }
    }

    cout << djs.countCountry() << endl;
    return 0;
}