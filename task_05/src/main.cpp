#include <iostream>
#include <tree.hpp>

int main() { 
    Tree<int> tree;

    tree.Insert(3, 1);
    tree.Insert(2, 1);
    tree.Insert(4, 2);

    return 0; 
}
