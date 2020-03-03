//NO.14的<>
//operato+不返回引用&
#include <iostream>
#include <cstring>

using namespace std;

template <class elemType> class mylist;
template <class elemType> mylist<elemType> operator+(const mylist<elemType> &l1,const mylist<elemType> &l2);

template<class elemType>
class mylist
{
    friend mylist<elemType> operator+<>(const mylist &l1,const mylist &l2);
public:
    elemType *data;
    int size;
    mylist(int initSize=1)
    {
        size=initSize;
        data = new elemType[size];
    }
    mylist(const mylist<elemType> &x);//拷贝构造函数
    mylist &operator=(const mylist &x);//赋值重载
    ~mylist(){delete []data;size=0;}
};

template<class elemType>//赋值重载
mylist<elemType> &mylist<elemType>::operator=(const mylist<elemType> &x)
{
    if (this == &x) return *this;
    size=x.size;
    delete []data;
    data= new elemType[size];
    for(int i=0;i<size;i++)data[i]=x.data[i];
    return *this;
}

template<class elemType>//拷贝构造函数
mylist<elemType>::mylist(const mylist<elemType> &x)
{
    size=x.size;
    elemType *data = new elemType[size];
    for(int i=0;i<size;i++)data[i]=x.data[i];
}

template<class elemType>
mylist<elemType> operator+(const mylist<elemType> &l1,const mylist<elemType> &l2)
{
    int i,j;
    mylist<elemType> l3(l1.size+l2.size);
    l3.size=l1.size+l2.size;
    for (i=0;i<l1.size;i++)l3.data[i]=l1.data[i];
    for (j=0;j<l2.size;j++)l3.data[i+j]=l2.data[j];
    return l3;
}


int main()
{
    char type[10];
    int len1,len2;
    cin >> type;
    cin >> len1 >> len2;

    if (!strcmp(type,"int"))
    {
        mylist<int> list1(len1),list2(len2),list3(len1+len2);
        for (int i=0;i<len1;i++)cin>>list1.data[i];list1.size=len1;
        for (int i=0;i<len2;i++)cin>>list2.data[i];list2.size=len2;
        list3 = list1+list2;
        for (int i=0;i<list3.size;i++)
            cout << list3.data[i]<<' ';
    }
    else if (!strcmp(type,"double"))
    {
        mylist<double> list1(len1),list2(len2),list3(len1+len2);
        for (int i=0;i<len1;i++)cin>>list1.data[i];list1.size=len1;
        for (int i=0;i<len2;i++)cin>>list2.data[i];list2.size=len2;
        list3 = list1+list2;
        for (int i=0;i<list3.size;i++)
            cout << list3.data[i]<<' ';
    }
    else if (!strcmp(type,"char"))
    {
        mylist<char> list1(len1),list2(len2),list3(len1+len2);
        for (int i=0;i<len1;i++)cin>>list1.data[i];list1.size=len1;
        for (int i=0;i<len2;i++)cin>>list2.data[i];list2.size=len2;
        list3 = list1+list2;
        for (int i=0;i<list3.size;i++)
            cout << list3.data[i]<<' ';
    }

    return 0;
}











