#include "hfTree.h"

template <class Type >
hfTree<Type>::hfTree(const Type *v,const int *w,int size)
{
    const int MAX_INT=32767;
    int min1,min2;//最小树，次小树的权值
    int x,y,i;//y最小树，x次小树的下标

    length = 2*size;
    elem =new Node [length];
    for (i=size;i<length;i++)
    {
        elem[i].weight = w[i-size];
        elem[i].data = v[i-size];
        elem[i].parent = elem[i].left = elem[i].right = 0;
    }

    for (i=size-1;i>0;i--)
    {
        min1 = min2 = MAX_INT;
        x= y = 0;
        for (int j=i+1;j<length;j++)//找最小和次小进行归并
        {
            if (elem[j].parent == 0){//未被并入
                if (elem[j].weight < min1){
                    min2 = min1;
                    min1 = elem[j].weight;
                    x = y;
                    y = j;
                }
                else if (elem[j].weight < min2) {
                  min2 = elem[j].weight;
                  x = j;
                }
            }
        }
        elem[i].weight = min1+min2;
        elem[i].left = x;
        elem[i].right = y;
        elem[i].parent = 0;
        elem[x].parent = i;
        elem[y].parent = i;
        cout << elem[i].weight << ' '<< x<< ' '<<y<<endl; 
    }
}

template<class Type >
void hfTree<Type>::getCode (hfCode result[])
{
    int size = length/2;
    int p,s;//s是追溯过程中正在处理的节点，p是s的父节点的下标

    for (int i=size;i<length;i++)
    {
        result[i-size].data = elem[i].data;
        result[i-size].code = "";
        p = elem[i].parent;
        s = i;
        while(p)//向根追溯
        {
            if (elem[p].left==s)
                result[i-size].code = '0'+result[i-size].code;
            else result[i-size].code = '1'+result[i-size].code;
            s = p;
            p = elem[p].parent;
        }
    }
}