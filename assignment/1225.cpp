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
    int num,i,appeared,access_now,count=0;
    cin>> num;
    int *array = new int [num];
    for (i=0;i<num;i++)
    {
        cin >> array[i];
    }
    quicksort(array,num);
    appeared=array[0]-1;//let appeared and access_now be defferent initialy
    for (i=0;i<num;i++)
    {   
        access_now = array[i];
        if (access_now==appeared)
            continue;
        else
        {
            count++;
            appeared = access_now;
        }          
    }
    cout << count;
    return 0;
}