#include <iostream>
using namespace std;

//直接插入排序
void simpleInsertSort(int a[],int size)
{
    int k;
    int tmp;
    for (int j=1;j<size;j++)
    {
        tmp = a[j];
        for (k=j-1;tmp<a[k]&&k>=0;k--)
            a[k+1] = a[k];
        a[k+1] = tmp;
    }
}

//希尔排序
void shellSort(int a[],int size)
{
    int step,i,j;
    int tmp;

    for(step = size/2;step>0;step/=2)
        for(i=step;i<size;i++)
        {
            tmp = a[i];
            for (j = i-step;j>=0&&a[j]>tmp;j-=step)
                a[j+step] = a[j];
            a[j+step] = tmp;
        }
}

//直接选择排序
void simpleSelectSort(int a[], int size) {
    int i, j, min;
    int tmp;
    for (i = 0; i < size - 1; i++)
    min = i;
    for (j = i; j < size; j++)
        if (a[j] < a[min])
        min = j;
    tmp = a[i];a[i] = a[min];a[min] = tmp;
}

//堆排序
void percolateDown(int a[], int hole,int size)
{
    int child;
    int tmp = a[hole];

    for (; hole * 2 + 1 < size;hole = child)
    {
        child = hole * 2 + 1;
        if (child!=size-1&&a[child+1]>a[child])
            child++;
        if (a[child]>a[hole])
            a[hole] = a[child];
        else
            break;
    }
    a[hole] = tmp;
}

void heapSort( int a[],int size)
{
    int i;
    int tmp;
    for (i = size / 2 - 1; i >= 0;i--)
        percolateDown(a, i, size);

    for (i = size - 1; i > 0;--i)
    {
        tmp = a[0];
        a[0] = a[i];
        a[i] = tmp;
        percolateDown(a, 0, i);
    }
}

//冒泡排序
void bubbleSort(int a[],int size)
{
    int i, j;
    int tmp;
    bool flag = true;

    for (i = 1; i < size&&flag;i++)//共需要size-1次冒泡
    {
        flag = false;
        for (j = 0; j < size - i;j++)
        {
            if (a[j+1]<a[j]){
                tmp = a[j + 1];
                a[j + 1] = a[j];
                a[j] = tmp;
                flag = true;
            }
        }
    }
}

//快速排序
int divide(int a[],int low,int high)
{
    int k = a[low];
    do
    {
        while(low<high&&a[high]>=k)
            high--;
        if(low<high)
            a[low++] = a[high];
        while(low<high&&a[low]<=k)
            low++;
        if (low<high)
            a[high--] = a[low];
    } while (low != high);
    a[low] = k;
    return low;
}

void quickSort(int a[],int low,int high)
{
    int mid;
    if (low>=high)//只有1个或0个元素
        return;
    mid = divide(a, low, high);
    quickSort(a, low, mid-1);
    quickSort(a, mid + 1, high);
}

void quickSort(int a[],int size)
{
    quickSort(a, 0, size - 1);
}

//归并排序
void merge(int a[],int left,int mid,int right)//mid是第二个数组的开头
{
    int *tmp = new int[right - left + 1];

    int i = left, j = mid, k = 0;

    while (i < mid && j<=right)
    {
        if (a[i]<a[j])
            tmp[k++] = a[i++];
        else
            tmp[k++] = a[j++];
    }

    while(i<mid)
        tmp[k++] = a[i++];
    while(j<=right)
        tmp[k++] = a[j++];

    for (i = 0, k = left; k <= right;)
        a[k++] = tmp[i++];
    delete[] tmp;
}

void mergeSort(int a[],int left,int right)
{
    int mid = (left + right) / 2;

    if (left==right)
        return;
    mergeSort(a, left, mid);
    mergeSort(a, mid + 1, right);
    merge(a, left, mid + 1, right);
}

void mergeSort(int a[],int size)
{
    mergeSort(a, 0, size - 1);
}

//基数排序,口袋排序
struct node{
    int data;
    node *next;

    node() { next = NULL; }
    node(int d) : data(d) { next = NULL; }
};

void bucketSort(node *&p)
{
    node *bucket[10], *last[10], *tail;
    int i, j, k, base = 1, max = 0, len = 0;

    for (tail = p; tail != NULL;tail = tail->next)
        if (tail->data>max)
            max = tail->data;

    if (max==0)
        len = 0;
    else while(max>0) {
        ++len;
        max /= 10;
    }

    for (i = 1; i <= len;i++)
        for (j = 0; j <= 9;j++)
            bucket[j] = last[j] = NULL;
        while(p!=NULL)
        {
            k = p->data / base % 10;
            if (bucket[k]==NULL)
                bucket[k] = last[k] = p;
            else
                last[k] = last[k]->next = p;
            p = p->next;
        }
        p = NULL;
        for (j = 0; j <= 9;j++)
        {
            if (bucket[j] ==NULL)
                continue;
            if (p==NULL)
                p = bucket[j];
            else
                tail->next = bucket[j];
            tail = last[j];
        }
        tail->next = NULL;
        base *= 10;
}

