#include<iostream>
#include"bstree.hpp"
#include"bstree.cpp"

int main(){
    Node<int> no;
    BSTree<char> tree;
    char elems[] = {'c','d','b','a','f','z','e','g'};
    
    for( char x: elems )
        tree.insert(x);
    
    tree.print_hierarchy();
    return 0;
}