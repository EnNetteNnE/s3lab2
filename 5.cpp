#include <iostream>
#include <algorithm>

#include "D.hpp"

using namespace std;



int main() {
    Tree tree;
    tree.insertNum(12);
    tree.insertNum(19);
    tree.insertNum(3);
    tree.insertNum(0);
    tree.insertNum(2);
    tree.insertNum(14);
    tree.insertNum(13);
    tree.insertNum(24);
    tree.insertNum(21);
    tree.insertNum(30);

    string result;
    printTree(result, tree.head, 0, "");

    cout << "Изначальное дерево\n";
    cout << result;

    tree.remove(tree.head, 19);

    result = "";
    printTree(result, tree.head, 0, "");

    cout << "Получившееся дерево\n";
    cout << result;
}
