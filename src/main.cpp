#include<iostream>
#include"bstree.hpp"
#include"bstree.cpp"

int main(){
    Node<int> no;
    BSTree<char> tree;
    BSTree<int> tree2;
    char elems[] = {'c','e','b','a','f','z','d','g'};
    int elems2[] = {50, 40, 60, 54, 65, 55, 58, 57, 56, 52, 61, 67, 45, 35};
    
    for( int x: elems2 )
        tree2.insert(x);
    
    tree2.print_hierarchy();
    std::cout << tree2.get_size();
    std::cout << "======================\n";
    std::cout << tree2.get_size();
    tree2.print_hierarchy();
    return 0;
}