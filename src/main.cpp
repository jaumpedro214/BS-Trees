#include"bstree.hpp"
#include"bstree.cpp"
#include<iostream>

#include<string>
#include<vector>
#include<fstream>

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

void read_files( std::string tree, std::string commands ){
    BSTree<int> bstree;
    int value;
    std::string command;
    std::string boolmapper[] = {"false", "true"};

    std::cout << "Input tree file - " << tree << std::endl;
    std::cout << "Commands file - " << commands << std::endl;
    std::ifstream treefile, commandsfile;

    treefile.open(tree, std::ifstream::in);
    commandsfile.open(commands, std::ifstream::in);

    std::cout << "Building tree...\n"; 
    while( treefile >> value ){
        bstree.insert(value);
    }
    bstree.print_hierarchy();
    for( int x: bstree.null_ptr_per_level )
        std::cout << x << " ";
    std::cout << "\n";

    std::cout << "Reading commands...\n";
    while( commandsfile >> command ){
        if( command == "ENESIMO" ){
            commandsfile >> value;
            std::cout << bstree.nth_elem(value);
        }
        else if( command == "POSICAO" ){
            commandsfile >> value;
            std::cout << bstree.position(value);
        }
        else if( command == "MEDIANA" ){
            std::cout << bstree.median();
        }
        else if( command == "CHEIA" ){
            std::cout << boolmapper[bstree.is_full()];
        }
        else if( command == "COMPLETA" ){
            std::cout << boolmapper[bstree.is_complete()];
        }
        else if( command == "IMPRIMA" ){
            std::cout << bstree.to_string();
        }
        else if( command == "REMOVA" ){
            commandsfile>>value;
            /*std::cout <<*/ boolmapper[bstree.remove(value)];

            bstree.print_hierarchy();
            for( int x: bstree.null_ptr_per_level )
                std::cout << x << " ";
            std::cout << "\n";
        }
        else if( command == "INSIRA" ){
            commandsfile>>value;
            std::cout << boolmapper[bstree.insert(value)];
        }
        std::cout << std::endl;
    }

    for( int x: bstree.null_ptr_per_level )
        std::cout << x << " ";
    std::cout << "\n";

    bstree.print_hierarchy();
    treefile.close();
    commandsfile.close();
}

int main(int argc, char *argv[]){
    std::vector<char> elems1 = {'G','B','D','A','H','F','C','E','K','I','W',};
    std::vector<int> elems2 = {100, 50, 150, 25, 75, 125, 175, 30, 20, 80, 70, 130, 120, 180, 170};
    std::vector<std::string> elems3 = {"Ronaldo", "Maria", "Pedro" , "Joao", "Vinicius", "Ziraldo", "Samanta", "Amanda"};
    
    //print_tree_info(elems1);
    //print_tree_info(elems2);
    //print_tree_info(elems3);

    if( argc == 3 ){
        read_files( std::string(argv[1]), std::string(argv[2]) );
    }
    
    return 0;
}