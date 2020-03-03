#include "bstree.cpp"

using namespace std;

int main()
{
    int array[] = { 10, 8, 21, 87, 56, 4, 11, 3, 22, 7 };
    bstree<int> tree;
    int *x=NULL, *p=NULL;

    for (int i = 0; i < 10; ++i)
        tree.insert(array[i]);

    p = tree.find(56);
    if (p)
        cout << "find 56 is " << p;
    else
        cout << "not found" << endl;
    tree.remove(56);
    p = tree.find(56);
    if (p)
        cout << "find 56 is " << *p;
    else
        cout << "not found" << endl;
    p = tree.find(21);
    if (p)
        cout << "find 21 is" << p;
    else
        cout << "not found" << endl;
    tree.remove(21);
    return 0;
}