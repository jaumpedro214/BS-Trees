#include<iostream>
#include"bstree.hpp"
#include"bstree.cpp"

int main(){
    Node<int> no;
    BSTree<char> tree;
    tree.insert('c');
    tree.insert('d');
    tree.insert('b');
    tree.insert('a');
    tree.insert('f');
    tree.insert('z');
    tree.pre_order();
    std::cout << "\n";
    tree.in_order();
    std::cout << "\n";
    tree.pos_order();
    return 0;
}