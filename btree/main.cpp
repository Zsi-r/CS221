#include <iostream>
#include "binaryTree.cpp"

using namespace std;

int main()
{
    binaryTree<char> tree;

    tree.creatTree('@');
    tree.preOrder();
    tree.midOrder();
    tree.postOrder();
    tree.levelOrder();
    /*printTree(tree, '@');*/
    tree.delLeft('L');
    tree.delRight('C');
    tree.delLeft('C');
    /*printTree(tree, '@');*/

    return 0;
}
