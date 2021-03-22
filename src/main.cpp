#include<iostream>
#include<string>
#include"bstree.hpp"
#include"bstree.cpp"

int main(){
    Node<int> no;
    BSTree<char> tree;
    BSTree<int> tree2;
    BSTree<std::string> tree3;
    char elems[] = {'F','B','C','A','H','G','D','E'};
    int elems2[] = {50, 40, 60, 54, 65, 55, 58, 57, 56, 52, 61, 67, 45, 35};
    std::string elems3[] = {"Joao", "Pedro", "Maria", "Ziraldo", "Francisco"};
    
    for( std::string x: elems3 )
        tree3.insert(x);

    for( int x: elems )
        tree.insert(x);

    
    tree.print_hierarchy();
    tree.remove('F'); std::cout << "\n\n";
    tree.print_hierarchy();
    return 0;
}