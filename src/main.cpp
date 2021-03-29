#include<iostream>
#include<string>
#include"bstree.hpp"
#include"bstree.cpp"

int main(){
    Node<int> no;
    BSTree<char> tree;
    BSTree<int> tree2;
    BSTree<std::string> tree3;
    char elems[] = {'G','B','D','A','H','F','C','E','K','I','W',};
    int elems2[] = {100, 50, 150, 25, 75, 125, 175, 30, 20, 80, 70, 130, 120, 180, 170};
    std::string elems3[] = {"Joao", "Pedro", "Maria", "Ziraldo", "Francisco"};
    
    for( int x: elems2 )
        tree2.insert(x);

    for( int x: elems )
        tree.insert(x);

    tree2.print_hierarchy();

    std::cout << tree2.get_size();
    std::cout << "\n";
    for( int i = 0 ; i < tree2.get_size(); i++ )
        std::cout << tree2.nth_elem(i) << " "; 
    std::cout << "\n";
    tree2.in_order();
    std::cout << "\n";
    for( int x: elems2 )
        tree2.position(x);
    std::cout << tree2.median();

    return 0;
}