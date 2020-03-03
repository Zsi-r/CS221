#ifndef BINARYTREE_H_INCLUDED
#define BINARYTREE_H_INCLUDED

#include "bTree.h"
#include "linkQueue.cpp"
#include "linkStack.cpp"

template <class T>
class binaryTree:public bTree<T>
{   
    friend void printTree(const binaryTree &t, T flag);
    private:
        struct Node{
            Node *left, *right;
            T data;

            Node() : left(NULL), right(NULL){};
            Node(T item, Node *L = NULL, Node *R = NULL):data(item),left(L),right(R){};
            ~Node(){};
        };

        struct StNode{
            Node *node;
            int TimesPop;

            StNode(Node *N = NULL) : node(N), TimesPop(0){};
        };

        Node *root;
    public:
        binaryTree() : root(NULL){};
        binaryTree(T x) { root = new Node(x); }
        ~binaryTree();
        void clear();
        bool isEmpty() const;
        T Root(T flag) const;
        T lchild(T x, T flag) const;
        T rchild(T x, T flag) const;
        void delLeft(T x);
        void delRight(T x);
        void preOrder() const;
        void midOrder() const;
        void postOrder() const;
        void levelOrder() const;
        void creatTree(T flag);//?
        T parent(T x, T flag) const { return flag; }//?
        int size() const;
        int height() const;

    private:
        Node *find(T x, Node *t) const;
        void clear(Node *&t);
        void preOrder(Node *t) const;
        void midOrder(Node *t) const;
        void postOrder(Node *t) const;
        int size(Node *t) const;
        int height(Node *t) const;
};  

#endif // BINARYTREE_H_INCLUDED
