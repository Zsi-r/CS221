#include <iostream>
#include <cstring>
#include <cmath>

using namespace std;

void post(const char tree[],int address)
{
    if (address >= strlen(tree))
        return;
    if (tree[address]=='@')
        return;
    post(tree, address * 2);
    post(tree, address * 2 + 1);
    cout << tree[address];
}

void f(int root , int start ,int end,int count,char tree[],const char pre[],const char mid[]){
    int i;
    if (end < start)
        return; 
    else
    {
        tree[count] = pre[root];
    }


    for (i = start; i <= end;i++)
        if (mid[i]==pre[root])
            break;
    f(root + 1, start, i - 1, 2 * count, tree, pre, mid);
    f(root + 1 + i - start, i + 1, end, 2 * count + 1, tree, pre, mid);
}

int main()
{
    char pre[100], mid[100];
    char tree[1000001];

    cin >> pre;
    cin >> mid;
    int len = strlen(pre);
    for (int k = 0; k<1000000 ;k++)
    {
        tree[k] = '@';
    }

    f(0, 0, len - 1, 1, tree, pre, mid);

    /*
    int num = 0, i = 1;
    while (num!=len)
    {
        if (tree[i]=='@')
            cout << "NULL" << ' ';
        else{
            cout << tree[i] << ' ';
            num++;
        }
        i++;
    }
    */

    post(tree, 1);

    return 0;
}