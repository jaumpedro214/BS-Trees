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
    int elems2[] = {50, 40, 60, 54, 65, 55, 58, 57, 56, 52, 61, 67, 45, 35, 12, -30, -12, -10 , -1, 123, 345, 333};
    std::string elems3[] = {"Joao", "Pedro", "Maria", "Ziraldo", "Francisco"};
    
    for( int x: elems2 )
        tree2.insert(x);

    for( int x: elems )
        tree.insert(x);

    tree2.remove(33);
    tree2.remove(333);
    tree2.remove(-1);
    tree2.remove(-10);
    tree2.remove(50);
    tree2.insert(2323);
    tree2.insert(11120);
    tree2.remove(11120);
    tree2.insert(-2);

    tree2.print_hierarchy();

    for( int i = 0 ; i < tree2.get_size(); i++ )
        std::cout << tree2.nth_elem(i) << " "; 
    std::cout << "\n";
    tree2.in_order();
    std::cout << "\n";

    return 0;
}