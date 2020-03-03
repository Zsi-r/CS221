#include "binaryTree.h"
#include <iostream>

using namespace std;

template <class T>
bool binaryTree<T>::isEmpty()const
{
    return root == NULL;
}

template <class T>
T binaryTree<T>::Root(T flag) const
{
    if(root == NULL)
        return flag;
    else
        return root->data;
}

template<class T>
void binaryTree<T>::clear(binaryTree<T>::Node *&t)
{
    if (t==NULL)
        return;
    clear(t->left);
    clear(t->right);
    delete t;
    t = NULL;
}

template <class T>
void binaryTree<T>::clear()
{
    clear(root);
}

template <class T>
binaryTree<T>::~binaryTree<T>()
{
    clear(root);
}

/*

template<class T>
void binaryTree<T>::preOrder(binaryTree<T>::Node *t)const
{
    if (t==NULL)
        return;
    cout << t->data <<' ';
    preOrder(t->left);
    preOrder(t->right);
}

template<class T>
void binaryTree<T>::preOrder()const
{
    cout << "\n preOrder Traverse: ";
    preOrder(root);
}

template <class T>
void binaryTree<T>::postOrder(binaryTree<T>::Node *t) const
{
    if (t==NULL)
        return;
    postOrder(t->left);
    postOrder(t->right);
    cout << t->data << ' ';
}

template <class T>
void binaryTree<T>::postOrder() const
{
    cout << "\n postOrder Traverse: ";
    postOrder(root);
}

template <class T>
void binaryTree<T>::midOrder(binaryTree<T>::Node *t) const
{
    if (t==NULL)
        return;
    midOrder(t->left);
    cout << t->data << ' ';
    midOrder(t->right);
}

template <class T>
void binaryTree<T>::midOrder() const
{
    cout << "\n midOrder Traverse: ";
    midOrder(root);
}

*/

template <class T>
void binaryTree<T>::levelOrder() const
{
    linkQueue<Node *> que;
    Node *tmp;

    cout << "\n levelOrder Traverse:";
    que.enQueue(root);

    while(!que.isEmpty()){
        tmp = que.deQueue();
        cout << tmp->data << ' ';
        if (tmp->left!=NULL)
            que.enQueue(tmp->left);
        if (tmp->right!=NULL)
            que.enQueue(tmp->right);
    }
}

template <class T> //从t节点开始向下寻找data==x的节点
typename binaryTree<T>::Node *binaryTree<T>::find(T x, binaryTree<T>::Node *t) const
{
    Node *tmp;
    if (t == NULL)
        return NULL;//从这个方向没有找到
    if (t->data== x)
        return t;
    if (tmp = find(x,t->left))
        return tmp;
    else
        return find(x, t->right);
}

template <class T>
void binaryTree<T>::delLeft(T x) //删除data为x的节点的左节点
{
    Node *tmp = find(x, root);
    if (tmp == NULL)
        return;
    clear(tmp->left);
}

template <class T>
void binaryTree<T>::delRight(T x)
{
    Node *tmp = find(x, root);
    if (tmp == NULL)
        return;
    clear(tmp->right);
}

template <class T> //返回data为x的节点的左节点的data，若没有该节点或没有子节点，则返回flag
T binaryTree<T>::lchild(T x, T flag) const
{
    Node *tmp = find(x, root);
    if (tmp == NULL || tmp->left == NULL)
        return flag;
    return tmp->left->data;
}

template <class T>
T binaryTree<T>::rchild(T x,T flag) const
{
    Node *tmp = find(x, root);
    if (tmp == NULL || tmp->right == NULL)
        return flag;
    return tmp->right->data;
}

template <class T>
void binaryTree<T>::creatTree(T flag)
{
    linkQueue<Node *> que;
    Node *tmp;
    T x, ldata, rdata;
    //创建树，输入flag为空,flag一般为@
    cout << "\n input root node: ";
    cin >> x;
    root = new Node(x);
    que.enQueue(root);

    while(!que.isEmpty())
    {
        tmp = que.deQueue();
        cout << "\n input the two sons of " << (tmp->data) << "(Empty node is expressed as " << flag <<" ) : ";
        cin >> ldata >> rdata;
        if (ldata!=flag)
            que.enQueue((tmp->left = new Node(ldata)));
        if (rdata!=flag)
            que.enQueue((tmp->right = new Node(rdata)));
    }

    cout << "create completed !"<<endl;
}



template <class T>
int binaryTree<T>::size() const
{
    return size(root);
}

template <class T>//以t为根的树的节点数
int binaryTree<T>::size(binaryTree<T>::Node *t) const
{
    if (t == NULL)
        return 0;
    return 1 + size(t->left) + size(t->right);
}

template <class T>
int binaryTree<T>::height() const
{
    return height(root);
}

template <class T>
int binaryTree<T>::height(binaryTree<T>::Node *t) const
{
    if (t == NULL)
        return 0;
    int lt = height(t->left);
    int rt = height(t->right);
    return 1 + ((lt > rt) ? lt : rt);
}

template <class T>
void printTree(const binaryTree<T> &t, T flag)
{
    linkQueue<T> q;
    q.enQueue(t.root->data);
    cout << endl;
    while(!q.isEmpty()){
        char p, l, r;//注意为节点的data类型为char
        p = q.deQueue();
        l = t.lchild(p, flag);
        r = t.rchile(p, flag);
        cout << p << ' ' << l << ' ' << r << endl;
        if (l!='@')
            q.enQueue(l);
        if (r!='@')
            q.enQueue(r);
    }
}

template <typename T>
void binaryTree<T>::preOrder()const
{
    linkStack<Node *> s;
    Node *current;

    cout << "\npreOrder Traverse: ";
    s.push(root);
    while (!s.isEmpty()){
        current = s.pop();
        cout << current->data<< ' ';
        if (current->right!=NULL)
            s.push(current->right);
        if (current->left!=NULL)
            s.push(current->left);
    }
}

template <typename T>
void binaryTree<T>::midOrder() const
{
    linkStack<StNode> s;
    StNode current(root);

    cout << "\nmidOrder Traverse: ";
    s.push(current);
    while(!s.isEmpty())
    {
        current = s.pop();
        if (++current.TimesPop ==2 ){//每次循环自动执行++current.TimesPop
            cout << current.node->data << ' ';
            if (current.node->right!=NULL)
                s.push(StNode(current.node->right));
        }
        else{
            s.push(current);
            if (current.node->left!=NULL)
                s.push(StNode(current.node->left));
        }
    }
}

template <class T>
void binaryTree<T>::postOrder() const
{
    linkStack<StNode> s;
    StNode current(root);

    cout << "\npostOrder Traverse: ";
    s.push(current);

    while(!s.isEmpty()){
        current = s.pop();
        if (++current.TimesPop == 3)
        {
            cout << current.node->data<<' ';
            continue;
        }
        s.push(current);
        if(current.TimesPop == 1){
            if (current.node -> left!=NULL)
                s.push(StNode(current.node->left));
        }
        else{
            if (current.node->right!=NULL)
                s.push(StNode(current.node->right));
        }
    }
}