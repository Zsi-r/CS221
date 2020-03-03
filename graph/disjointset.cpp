#include <iostream>
#include <cstdlib>
#include <ctime>
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

//不相交集的应用：创建迷宫
void creatPuzzle(int size)
{
    int num1, num2;
    DisjointSet ds(size * size);

    srand(time(0));

    while(ds.Find(0)!=ds.Find(size*size-1))
    {
        while(true)
        {
            num1 = rand() * size * size / (RAND_MAX + 1);
            num2 = num1 - size;//上方
            if(num2>=0&&ds.Find(num1)!=ds.Find(num2))
                break;
            num2 = num1 - 1;
            if (num1%size!=0&&ds.Find(num1)!=ds.Find(num2))
                break;
            num2 = num1 + size;
            if (num2<size*size&&ds.Find(num1)!=ds.Find(num2))
                break;
            num2 = num1 + 1;
            if (num2 % size != 0&&ds.Find(num1)!=ds.Find(num2))
                break;
        }
        ds.Union(ds.Find(num1), ds.Find(num2));
        cout << num1 << ',' << num2 << endl;
    }
}