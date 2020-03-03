#include <iostream>
#include <cmath>
#include <cstring>

using namespace std;

class poly
{
    friend int cal(const poly &tmp, int x) { return tmp.a * x * x + tmp.b * x + tmp.c; }
public:
    int a, b, c;
    int minx; //if (minx>0) plus 1 each time;else minus;
    bool grater0;
    int miny;
    bool haveaddfirst = false;
    poly(){};
    poly(int a1,int b1,int c1):a(a1),b(b1),c(c1){
        minx = -b / 2 / a;
        miny = a * minx * minx + b * minx + c;
        if (b<=0)
            grater0 = true;
        else
            grater0 = false;
    }
    ~poly(){};
};

class priorityQueue
{
public:
    priorityQueue(){};
    priorityQueue(int capacity);
    ~priorityQueue();
    void enQueue(int x);
    int deQueue();
    int getHead() const;
private:
    int currentSize;
    int *array;
    int maxSize;

    void doubleSpace();
    void buildHeap();
    void percolateDown(int hole);
};

priorityQueue::priorityQueue(int capacity)
{
    array = new int[capacity];
    maxSize = capacity;
    currentSize = 0;
}

priorityQueue::~priorityQueue()
{
    delete[] array;
}

int priorityQueue::getHead() const
{
    return array[1];
}

void priorityQueue::enQueue(int x)
{
    if (currentSize == maxSize-1)//因为array[0]不放东西
        doubleSpace();
    
    //向上过滤
    int hole = ++currentSize;
    for (; hole > 1 && x > array[hole / 2]; hole /= 2)
        array[hole] = array[hole / 2];
    array[hole] = x;
}

int priorityQueue::deQueue()
{
    int maxItem;
    maxItem = array[1];
    array[1] = array[currentSize--];
    percolateDown(1);
    return maxItem;
}

void priorityQueue:: percolateDown(int hole)//向下过滤
{
    int child;
    int tmp = array[hole];
    for (; hole * 2 <= currentSize; hole = child){
        child = hole * 2;
        if (child!=currentSize && array[child+1]>array[child])//找大的儿子，如果child==currentSize，则没有右儿子
            child++;
        if(array[child]>tmp)
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
    int *tmp = array;
    maxSize *= 2;
    array = new int[maxSize];
    for (int i = 1; i <= currentSize; i++) //当currentSize == maxSize-1时，调用intSpace()
        array[i] = tmp[i];
    delete[] tmp;
}

int main()
{
    int a, b, c;
    int n, k,count,countforadd;
    cin >> n >> k;
    bool flag = false;
    poly *polyarray = new poly[n];
    priorityQueue output(k+1);
    for (int i = 0; i < n;i++)
    {
        cin >> a >> b >> c;
        poly tmp(a,b,c);
        polyarray[i] = tmp;
    }
    //初始化
    if (n>=k)
        for (int i = 0; i < k;i++)
        {
            polyarray[i].haveaddfirst = true;
            output.enQueue(polyarray[i].miny);
        }
    else
        {
            flag = true;
            for (int i = 0; i < n;i++){
                output.enQueue(polyarray[i].miny);
                polyarray[i].haveaddfirst = true; 
            }
            count = n+1;
            countforadd = count;
            while(true)
            {
                if (polyarray[0].grater0)
                {
                    if (count > k)
                        break;
                    output.enQueue(cal(polyarray[0], polyarray[0].minx + (countforadd-n)));
                    count++;
                    if (count > k)
                    {   
                        if (cal(polyarray[0], polyarray[0].minx - (countforadd-n))<output.getHead())
                        {
                            output.deQueue();
                            output.enQueue(cal(polyarray[0], polyarray[0].minx - (countforadd-n)));
                            countforadd++;
                            count++;
                        }
                        break;
                    }
                    else{
                        output.enQueue(cal(polyarray[0], polyarray[0].minx - (countforadd-n)));
                        count++;
                        countforadd++;
                    }
                }
                else
                {
                    if (count > k)
                        break;
                    output.enQueue(cal(polyarray[0], polyarray[0].minx - (countforadd-n)));
                    count++;
                    if (count > k)
                    {   
                        if (cal(polyarray[0], polyarray[0].minx + (countforadd-n))<output.getHead())
                        {
                            output.deQueue();
                            output.enQueue(cal(polyarray[0], polyarray[0].minx + (countforadd-n)));
                            count++;
                            countforadd++;
                        }
                        break;
                    }
                    else{
                        output.enQueue(cal(polyarray[0], polyarray[0].minx + (countforadd-n)));
                        count++;
                        countforadd++;
                    }

                }
            }
        }
    //for (int i = 0; i < k;i++)
    //{
    //    cout << output.deQueue() << ' ';
    //}
    for (int i = 0; i < n;i++)
    {
        bool plus=false;
        if (polyarray[i].grater0)
            plus = true;
        int sumplus,summinus;
        int j;
        if (i == 0 && flag == true)
        {
            j = countforadd - n;
        }
        else
            j = polyarray[i].haveaddfirst;

        for (;;j++)
        {
            sumplus = cal(polyarray[i], polyarray[i].minx + j);
            summinus = cal(polyarray[i], polyarray[i].minx - j);
            if (plus)
            {   
                if (sumplus>output.getHead())
                    break;
                output.deQueue();
                output.enQueue(sumplus);
                if (j==0)
                    continue;
                if (summinus>output.getHead())
                    break;
                output.deQueue();
                output.enQueue(summinus);
            }
            else if(!plus)
            {   
                if (summinus>output.getHead())
                    break;
                output.deQueue();
                output.enQueue(summinus);
                if (j ==0)
                    continue;
                if (sumplus>output.getHead())
                    break;
                output.deQueue();
                output.enQueue(sumplus);
            }
        }
    }
    int *outputarray = new int[k];
    for (int i = k - 1; i >= 0; i--)
    {
        outputarray[i] = output.deQueue();
    }
    for (int i = 0; i < k;i++)
    {
        cout << outputarray[i] << ' ';
    }
    delete[] outputarray;
    delete[] polyarray;
    return 0;
}