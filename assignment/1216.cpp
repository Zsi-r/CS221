#include <cstring>
#include <iostream>

using namespace std;

class prioQueue
{
public:
    int *array;
    int currentSize;
    int maxSize;
    prioQueue(int capacity = 2) : currentSize(0), maxSize(capacity) { array = new int[maxSize]; }
    ~prioQueue() { delete[] array; }
    void insert(int x);
    int find(int x);
    void decrease(int index, int sub);
    void doublespace();
    void percolateDown(int hole);
};

void prioQueue::doublespace()
{
    int *tmp = array;
    maxSize = maxSize * 2;
    array = new int[maxSize];
    for (int i = 0; i <= currentSize; i++)
        array[i] = tmp[i];
    delete[] tmp;
}

void prioQueue::insert(int x)
{
    if (currentSize == maxSize - 1)
        doublespace();
    int hole = ++currentSize;
    for (; hole > 1 && x< array[hole / 2]; hole /= 2)
        array[hole] = array[hole / 2];
    array[hole] = x;
}

/*
int prioQueue::find(int x) //找出优先级值大于x的最小的元素，输出其下标
{
    if (array[1] == x)
    {
        if (currentSize == 2)
            return 2;
        else
            return ((array[2] <= array[3]) ? 2 : 3);
    }
    int xaddress = 1;
    for (int i = 1; i <= currentSize; i++)
        if (array[i] == x)
        {
            xaddress = i;
            break;
        }
    int maxaddress = ((xaddress * 2 <= currentSize) ? (xaddress * 2) : currentSize);
    int tmp = array[maxaddress];
    int tmpaddress = maxaddress;
    for (int i = xaddress / 2; i <= maxaddress; i++)
    {
        if (array[i] > x && array[i] < tmp)
        {
            tmp = array[i];
            tmpaddress = i;
        }
    }
    return tmpaddress;
}
*/

int prioQueue::find (int x)
{   
    int tmp  = 1,i =1;
    for (;tmp<currentSize;tmp++)
    {
        if (array[tmp]>x) break;
    }
    for (i = tmp ;i<= currentSize;i++)
    {   
        if (array[i]>x && array[i]<array[tmp])
            tmp = i;
    }
    return tmp;
}

void prioQueue::decrease(int index, int sub)
{
    array[index] -= sub;
    int tmp = array[index];
    //percolateDown(1);
    for (; index > 1 && tmp < array[index / 2]; index /= 2)
    {
        array[index] = array[index / 2];
    }
    array[index] = tmp;
}

void prioQueue::percolateDown(int hole)
{
    int child;
    int tmp = array[hole];
    for (; hole * 2 <= currentSize; hole = child)
    {
        child = hole * 2;
        if (child != currentSize && array[child + 1] < array[child])
            child++;
        if (array[child] < tmp)
            array[hole] = array[child];
        else
            break;
    }
    array[hole] = tmp;
}

int main()
{
    int line;
    char operation[10];
    int index, num;
    cin >> line;
    int *output = new int[line];
    int j = 0;
    prioQueue que;
    for (int i = 0; i < line; i++)
    {
        cin >> operation;
        if (strcmp(operation, "insert") == 0)
        {
            cin >> num;
            que.insert(num);
        }
        else if (strcmp(operation, "find") == 0)
        {
            cin >> num;
            output[j] = que.find(num);
            j++;
        }
        else if (strcmp(operation, "decrease") == 0)
        {
            cin >> index >> num;
            que.decrease(index, num);
        }
        //cout << endl;
        //cout << "que : ";
        //for (int t = 1;t<=que.currentSize;t++)
        //    cout << que.array[t]<<' ';
    }

    for (int k = 0; k < j; k++)
        cout << output[k] << endl;

    return 0;
}