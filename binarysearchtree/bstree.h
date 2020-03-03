#ifndef BSTREE_H_INCLUDED
#define BSTREE_H_INCLUDED

#include <iostream>

using namespace std;

template <class T>
class bstree
{
private:
    struct bstnode
    {
        T data;
        bstnode *left, *right;

        bstnode(const T &d, bstnode *l = NULL, bstnode *r = NULL) : data(d), left(l), right(r){};
    };

    bstnode *root;
public:
    bstree() { root = NULL; }
    ~bstree() { makeEmpty(root); }
    T *find(const T &x) const { return find(x, root); }
    void insert(const T &x){insert(x, root);}
    void remove(const T &x) { remove(x, root); }
private:
    void insert(const T &x, bstnode *&t);
    void remove(const T &x, bstnode *&t);
    T *find(const T &X, bstnode *t) const;
    void makeEmpty(bstnode *t);
};

#endif // BSTREE_H_INCLUDED
