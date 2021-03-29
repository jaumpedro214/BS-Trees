#include"bstree.hpp"
#include"bstree.cpp"
#include<iostream>

#include<string>
#include<vector>

template <class T>
void print_tree_info( std::vector<T> elems ){
    BSTree<T> tree;

    std::cout << std::endl;
    for( T x: elems ){
        tree.insert(x);
    }
    tree.print_hierarchy();
    std::cout << std::endl;
    std::cout << "Tree size - " << tree.get_size() << std::endl;
    std::cout << "Tree is complete - " << tree.is_complete() << std::endl;
    std::cout << "Tree is full - " << tree.is_full() << std::endl;
    std::cout << "Pre order path - ";
    tree.pre_order();
    
    std::cout << std::endl;
    std::cout << "By-level path to string - " << tree.to_string() << std::endl;
    std::cout << "Tree median - " << tree.median() << std::endl;

    std::cout << std::endl << "Find nth-element of pre-order" << std::endl;
    std::cout << "Tree 0th element - " << tree.nth_elem(0) << std::endl;
    std::cout << "Tree 1th element - " << tree.nth_elem(1) << std::endl;
    std::cout << "Tree 5th element - " << tree.nth_elem(5) << std::endl;

    std::cout << std::endl << "Find the position of a element in pre-order" << std::endl;
    std::cout << "Position of " << tree.nth_elem(6) << " - " << tree.position(tree.nth_elem(6)) << std::endl;
    std::cout << "Position of " << tree.nth_elem(3) << " - " << tree.position(tree.nth_elem(3)) << std::endl;
    std::cout << "Position of " << tree.nth_elem(0) << " - " << tree.position(tree.nth_elem(0)) << std::endl;
}

int main(){
    std::vector<char> elems1 = {'G','B','D','A','H','F','C','E','K','I','W',};
    std::vector<int> elems2 = {100, 50, 150, 25, 75, 125, 175, 30, 20, 80, 70, 130, 120, 180, 170};
    std::vector<std::string> elems3 = {"Ronaldo", "Maria", "Pedro" , "Joao", "Vinicius", "Ziraldo", "Samanta", "Amanda"};
    
    print_tree_info(elems1);
    print_tree_info(elems2);
    print_tree_info(elems3);
    
    return 0;
}