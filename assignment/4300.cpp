#include <iostream>

using namespace std;

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

int main()
{
    int N ,*array;
    cin >> N;
    array = new int[N];
    for (int i =0;i<N;i++)
    {
        cin >> array[i];
    }
    quickSort(array, N);
    cout << array[N / 2];
    return 0;
}