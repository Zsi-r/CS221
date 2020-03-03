#include <iostream>

using namespace std;

class set
{
    friend istream &operator>>(istream &is, set &x)
    {
        for (int i = 0; i < x.max; i++)
            is >> x.array[i];
        x.current_length = x.max;
        x.sort(x.array);
        return is;
    }
    friend ostream &operator<<(ostream&os,const set &x)
    {
        for (int i =0;i<x.current_length;i++)
            os << x.array[i]<<' ';
        return os;
    }
public:
    int max;
    int current_length;
    int *array;

    set(int n)
    {
        max = n;
        current_length = 0;
        array = new int[max];
    }
    ~set() { delete[] array; }

    void sort(int x[])
    {
        mergeSort(x, 0, current_length-1);
    }
    void mergeSort(int a[],int left ,int right);
    void merge(int a[],int left,int mid,int right);
    void plus(set &x);
    void minus(set &x);
    void intersection(set &x);
};

void set::merge(int a[],int left,int mid,int right)
{
    int *tmp = new int [right-left+1];

    int i=left,j =mid,k =0;

    while (i < mid && j <= right) {
      if (a[i] < a[j])
        tmp[k++] = a[i++];
      else
        tmp[k++] = a[j++];
    }

    while (i < mid)
      tmp[k++] = a[i++];
    while (j <= right) tmp[k++] = a[j++];

    for (i =0,k=left;k<=right;)a[k++] = tmp[i++];
    delete []tmp;
}

void set::mergeSort(int a[], int left, int right)
{
    int mid = (left+right)/2;

    if (left == right) return ;
    mergeSort(a, left, mid);
    mergeSort(a, mid+1, right);
    merge(a,left,mid+1,right);
}

void set::plus(set &x)
{
    set temp(x.current_length + current_length);
    int num1, num2, i = 0, j = 0;

    while (i < x.current_length && j < current_length)
    {
        num1 = x.array[i];
        num2 = array[j];
        if (num1 < num2)
        {
            temp.array[temp.current_length++] = num1;
            i++;
        }
        else if (num2 < num1)
        {
            temp.array[temp.current_length++] = num2;
            j++;
        }
        else if (num2 == num1)
        {
            temp.array[temp.current_length++] = num1;
            i++;
            j++;
        }
    }
    while (i < x.current_length)
    {
        temp.array[temp.current_length++] = x.array[i++];
    }
    while (j < current_length)
    {
        temp.array[temp.current_length++] = array[j++];
    }

    delete[] array;
    max = temp.current_length;
    current_length = 0;
    array = new int[max];
    for (; current_length < temp.current_length; current_length++)
    {
        array[current_length] = temp.array[current_length];
    }
}

void set::minus(set &x)
{
    int size = (current_length > x.current_length) ? current_length : x.current_length;
    set temp(size);

    int i = 0, j = 0;
    while (i < current_length && j < x.current_length)
    {
        if (array[i] < x.array[j])
            temp.array[temp.current_length++] = array[i++];
        else if (array[i] == x.array[j])
        {
            i++;
            j++;
        }
        else if(array[i]>x.array[j])
            j++;
    }
    while(i<current_length)temp.array[temp.current_length++] = array[i++];

    delete[]array;
    max = temp.current_length;
    array = new int [max];
    current_length = 0;
    for (;current_length<temp.current_length;current_length++)
    {
        array[current_length] = temp.array[current_length];
    }
}

void set::intersection(set&x)
{
    int size = (current_length > x.current_length) ? current_length : x.current_length;
    set temp(size);

    int i=0,j=0;
    while(i<current_length&&j<x.current_length)
    {   
        if (array[i]==x.array[j]){
            temp.array[temp.current_length++] = array[i];
            i++;
            j++;
        }
        else if (array[i]<x.array[j]) i++;
        else if (array[i]>x.array[j]) j++;
    }

    delete []array;
    max = temp.current_length;
    array = new int[max];
    current_length = 0;
    for (;current_length<temp.current_length;current_length++)
    {
        array[current_length] = temp.array[current_length];
    }
}

int main()
{   
    int lines,numofelem;
    cin >> lines;
    char op;

    set set1(100);
    
    for (int i=0;i<lines;i++)
    {
        cin >>op;
        cin >>numofelem;
        set temp(numofelem);
        cin >> temp;
        if (op=='+')
            set1.plus(temp);
        else if (op=='-')
            set1.minus(temp);
        else if (op=='*')
            set1.intersection(temp);
        cout << set1 <<endl;
    }
    return 0;
}