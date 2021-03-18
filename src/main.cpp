#include<iostream>
#include"bstree.hpp"
#include"bstree.cpp"

int main(){
    Node<int> no;
    BSTree<char> tree;
    tree.insert('c');
    std::cout << tree.get_root()->get_content();
    return 0;
}