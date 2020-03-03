#include "bstree.h"

template <class T>
T *bstree<T>::find(const T &x, bstnode *t) const
{
    if (t==NULL||t->data ==x)
        return (T *)t;
    if (t->data>x)
        return find(x,t->left);
    else
        return find(x, t->right);
}

template<class T>
void bstree<T>::makeEmpty(bstnode *t)
{
    if (t==NULL)
        return;
    makeEmpty(t->left);
    makeEmpty(t->right);
    delete t;
}

template<class T>
void bstree<T>::insert(const T&x,bstnode *&t)
{
    if (t==NULL)
        t = new bstnode(x);
    else if(t->data<x)
        insert(x, t->right);
    else if (t->data>x)
        insert(x,t->left);
}

template <class T>
void bstree<T>::remove(const T &x,bstnode *&t)
{
    if (t==NULL)
        return;
    if (x<t->data)
        remove(x, t->left);
    else if (x>t->data)
        remove(x, t->right);
    else if (t->left!=NULL&&t->right!=NULL)//被删节点有两个孩子
    {
        bstnode *tmp = t->right;
        while(tmp->left!=NULL)
            tmp = tmp->left;
        t->data = tmp->data;
        remove(t->data, t->right);
    }
    else//被删节点只有一个孩子或没有孩子
    {
        bstnode *oldnode = t;
        t = (t->left != NULL) ? t->left : t->right;
        delete oldnode;
    }
}