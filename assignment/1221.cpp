#include <iostream>
#include <cstring>

using namespace std;

struct bstnode
{
    int data;
    bstnode *left, *right;
    bstnode(int d, bstnode *l = NULL, bstnode *r = NULL) : data(d), left(l), right(r){};
    bstnode(){};
};

struct StNode{
    bstnode *node;
    int TimesPop;

    StNode(bstnode *N = NULL) : node(N), TimesPop(0){};
};

struct stacknode
{
    StNode data;
    stacknode *next;
    stacknode(const StNode d, stacknode *n = NULL):data(d),next(n){};
    stacknode():next(NULL){};
    ~stacknode(){};
};


class stack
{
private:
    stacknode *top_p;

public:
    stack() { top_p = NULL; }
    ~stack()
    {
        stacknode *temp = top_p;
        while(top_p!=NULL){
            top_p = top_p->next;
            delete temp;
            temp = top_p;
        }
    }
    bool isempty() { return top_p == NULL; }
    void push(const StNode&x)
    {
        top_p = new stacknode(x, top_p);
    }
    StNode pop()
    {
        stacknode *temp = top_p;
        StNode value = temp->data;
        top_p = top_p->next;
        delete temp;
        return value;
    }
};


class bst
{
public:
    bstnode *root;

    void insert(int d,bstnode* &n)
    {
        if (n == NULL)
            n = new bstnode(d);
        else if (n->data<d)
            insert(d, n->right);
        else if (d<=n->data)
            insert(d, n->left);
    }
    void remove(int d,bstnode* &n)
    {
        if (n==NULL)
            return;
        else if (n->data>d)
            remove(d, n->left);
        else if (n->data<d)
            remove(d, n->right);
        else if (n->left!=NULL&&n->right!=NULL)
        {
            bstnode *temp = n->right;
            while (temp->left!=NULL)
                temp = temp->left;
            n->data = temp->data;
            remove(n->data,n->right);
        }
        else
        {
            bstnode *temp = n;
            n = (n->left != NULL) ? n->left : n->right;
            delete temp;
        }
    }
    void find (int x,bstnode *n) const
    {
        if (n==NULL)
        {
            cout << 'N' << endl;
            return;
        }
        if(n->data==x)
        {
            cout << 'Y' << endl;
            return;
        }
        else if (n->data<x)
            return find(x, n->right);
        else if (n->data>x)
            return find(x, n->left);
    }

public:
    bst() { root = NULL; }
    ~bst(){};

    void find(int x)
    {
        find(x, root);
    }

    void find_ith(int i)
    {
        int count = 0;
        bool flag = false;
        stack s;
        StNode current(root);
        s.push(current);
        while(!s.isempty())
        {
            current = s.pop();
            if (++current.TimesPop==2){
                count++;
                if (count == i)
                {
                    flag = true;
                    cout << current.node->data << endl;
                    return;
                }
                if (current.node->right!=NULL)
                    s.push(StNode(current.node->right));
            }
            else
            {
                s.push(current);
                if (current.node->left!=NULL)
                    s.push(StNode(current.node->left));
            }
        }
        if (!flag)
            cout << 'N' << endl;
    }

    void delete_greater_than(int x,bstnode *&n)
    {   
        if (n==NULL)
            return;
        if (n->data<=x)
            delete_greater_than(x, n->right);
        else if (n->data>x)
        {
            delete_greater_than(x, n->right);
            delete_greater_than(x, n->left);
            remove(n->data, n);
        }
    }

    void delete_less_than(int x,bstnode *&n)
    {
        if (n==NULL)
            return;
        delete_less_than(x, n->left);
        delete_less_than(x, n->right);
        if (n->data<x)
            remove(n->data, n);
    }

    void delete_interval(int a ,int b,bstnode *&n)
    {
        if (n==NULL)
            return;
        delete_interval(a, b, n->left);
        delete_interval(a, b, n->right);
        if (n->data>a && n->data<b)
            remove(n->data, n);
    }
};

int main()
{
    int n,num,a,b;
    char s[20];
    bst tree;
    cin >> n;
    for (int i = 0; i < n;i++)
    {
        cin >> s;
        if(strcmp(s,"insert")==0){
            cin >> num;
            tree.insert(num, tree.root);
        }
        else if (strcmp(s,"delete")==0)
        {
            cin >> num;
            tree.remove(num, tree.root);
        }
        else if (strcmp(s,"find")==0)
        {
            cin >> num;
            tree.find(num);
        }
        else if  (strcmp(s,"find_ith")==0)
        {
            cin >> num;
            tree.find_ith(num);
        }
        else if (strcmp(s,"delete_greater_than")==0)
        {
            cin >> num;
            tree.delete_greater_than(num, tree.root);
        }
        else if (strcmp(s,"delete_less_than")==0)
        {
            cin >> num;
            tree.delete_less_than(num, tree.root);
        }
        else if (strcmp(s,"delete_interval")==0)
        {
            cin >> a >> b;
            tree.delete_interval(a, b, tree.root);
        }
    }
    return 0;
}