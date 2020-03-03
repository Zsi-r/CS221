#include <iostream>

using namespace std;

class poly
{
    friend int cal(const poly &tmp, int x) { return tmp.a * x * x + tmp.b * x + tmp.c; }
public:
    int a, b, c;
    int enQueuetimes = 0;
    int minx; //if (minx>0) plus 1 each time;else minus;
    bool grater0;
    int miny;
    bool leftrightleft = false;
    poly(){};
    poly(int a1,int b1,int c1):a(a1),b(b1),c(c1){
        minx = -b /(2*a);
        if (b<=0)
            grater0 = true;
        else
            grater0 = false;
        if (grater0 && -b%(2*a)<=a )
        {   
            miny = a*minx*minx +b*minx+c;
        }
        else if (grater0 && -b%(2*a)>a)
        {   
            minx++;
            leftrightleft  = true;
            miny = a*minx*minx +b*minx+c;
        }
        else if (!grater0 && b%(2*a)>a)
        {
            minx--;
            miny = a*minx*minx +b*minx+c;
        }
        else if(!grater0 && b%(2*a)<=a)
        {   
            leftrightleft = true;
            miny = a*minx*minx +b*minx+c;
        }
    }
    ~poly(){};
};

class priorityQueue
{
public:
    priorityQueue(){};
    priorityQueue(int capacity);
    ~priorityQueue();
    void enQueue(const poly &x);
    poly deQueue();
    poly getHead() const;
    int currentSize;
    poly *array;
    int maxSize;

    void doubleSpace();
    void buildHeap();
    void percolateDown(int hole);
};

priorityQueue::priorityQueue(int capacity)
{
    array = new poly[capacity];
    maxSize = capacity;
    currentSize = 0;
}

priorityQueue::~priorityQueue()
{
    delete[] array;
}

poly priorityQueue::getHead() const
{
    return array[1];
}

void priorityQueue::enQueue(const poly &x)
{
    if (currentSize == maxSize-1)//因为array[0]不放东西
        doubleSpace();
    
    //向上过滤
    int hole = ++currentSize;
    for (; hole > 1 && x.miny < array[hole / 2].miny; hole /= 2)
        array[hole] = array[hole / 2];
    array[hole] = x;
}

poly priorityQueue::deQueue()
{
    poly minItem;
    minItem = array[1];
    array[1] = array[currentSize--];
    percolateDown(1);
    return minItem;
}

void priorityQueue:: percolateDown(int hole)//向下过滤
{
    int child;
    poly tmp = array[hole];
    for (; hole * 2 <= currentSize; hole = child){
        child = hole * 2;
        if (child!=currentSize && array[child+1].miny<array[child].miny)//找小的儿子，如果child==currentSize，则没有右儿子
            child++;
        if(array[child].miny<tmp.miny)
            array[hole] = array[child];
        else
            break;
    }
    array[hole] = tmp;
}

void priorityQueue::buildHeap()
{
    for (int i = currentSize / 2; i > 0;i--)
        percolateDown(i);
}

void priorityQueue::doubleSpace()
{
    poly *tmp = array;
    maxSize *= 2;
    array = new poly[maxSize];
    for (int i = 0; i <= currentSize; i++) //当currentSize == maxSize-1时，调用doubleSpace()
        array[i] = tmp[i];
    delete[] tmp;
}

int main()
{
    int a, b, c, count = 0,tmpx;
    int n, k;
    cin >> n >> k;
    poly *polyarray = new poly[n+1];
    priorityQueue output(k+1);
    for (int i = 0; i < n;i++)
    {
        cin >> a >> b >> c;
        poly tmp(a,b,c);
        polyarray[i] = tmp;
    }

    for (int i = 0; i < n;i++)
    {
        output.enQueue(polyarray[i]);
    }
    /*
    for (int i = 0; i < n;i++)
    {
        cout << output.array[i + 1].miny << endl;
    }
    */
    while(count < k)
    {
        poly temp = output.deQueue();
        cout << temp.miny<< ' ';
        count++;
        temp.enQueuetimes++;
        if (temp.leftrightleft && temp.enQueuetimes%2==1){
            tmpx = temp.minx - (temp.enQueuetimes + 1) / 2;
            temp.miny = cal(temp, tmpx);
            output.enQueue(temp);
        }
        else if (temp.leftrightleft && temp.enQueuetimes%2==0){
            tmpx = temp.minx + temp.enQueuetimes / 2;
            temp.miny = cal(temp, tmpx);
            output.enQueue(temp);
        }
        else if (!temp.leftrightleft && temp.enQueuetimes%2==1){
            tmpx = temp.minx + (temp.enQueuetimes + 1) / 2;
            temp.miny = cal(temp, tmpx);
            output.enQueue(temp);
        }
        else if (!temp.leftrightleft && temp.enQueuetimes%2==0){
            tmpx = temp.minx - temp.enQueuetimes / 2;
            temp.miny = cal(temp, tmpx);
            output.enQueue(temp);
        }
        //cout << "test : " << temp.miny << endl;
    }
    return 0;
}