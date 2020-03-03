#include <iostream>

using namespace std;

int divide(int array[],int low,int high)
{
    int temp = array[low];
    do{
        while(low<high&&array[high]>=temp)high--;
        if (low<high) array[low++] = array[high];
        while(low<high&&array[low]<=temp)low++;
        if(low<high) array[high--]=array[low];
    }while(low!=high);
    array[low] = temp;
    return low;
}

void quicksort(int array[],int low,int high)
{
    int mid;
    if (low>=high) return ; 
    mid = divide(array,low,high);
    quicksort(array,low,mid-1);
    quicksort(array,mid+1,high);
}

void quicksort(int array[],int size)
{
    quicksort(array,0,size-1);
}

int main()
{
    int num,i;
    cin>> num;
    int *array = new int [num];
    for (i=0;i<num;i++)
    {
        cin >> array[i];
    }
    quicksort(array,num);
    for (i=0;i<num;i++)
    {   
        cout <<array[i] << ' ';
    }
    return 0;
}