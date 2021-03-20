#include<iostream>
#include"bstree.hpp"
#include"bstree.cpp"

int main(){
    Node<int> no;
    BSTree<char> tree;
    BSTree<int> tree2;
    char elems[] = {'c','e','b','a','f','z','d','g'};
    int elems2[] = {50, 40, 60, 54, 65, 55, 58, 57, 56, 52, 61, 67, 45, 35};

    for( char x: elems )
        tree.insert(x);
    for( int x: elems2 )
        tree2.insert(x);
    
    tree2.print_hierarchy();
    tree2.remove(65);
    tree2.remove(54);
    std::cout << "======================\n";
    tree2.print_hierarchy();
    return 0;
}