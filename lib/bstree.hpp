#ifndef BSTREE_HPP
#define BSTREE_HPP

#include <iostream>
#include <string>
#include <algorithm> // max

template <class T>
class Node{
    template<class U> friend class BSTree;
    private:
        T content;
        int height = 0;
        Node<T> *left=nullptr, *right=nullptr;
    public:
        // Constructors & Destructors
        Node();
        Node(T content);
        ~Node();
        // Methods
        T get_content();
};

template <class T = int> 
class BSTree{
    private:
        Node<T> *root=nullptr;
        int altura = 0;
        int size = 0;

        bool insert_at( const T &content, Node<T> *ptr );
        Node<T>* find_at(const T &content, Node<T> *ptr);

        void pre_order(Node<T> *root);
        void in_order(Node<T> *root);
        void pos_order(Node<T> *root);

        void print_hierarchy(Node<T> *root, std::string s);
    public:
        // Constructors & Destructors
        ~BSTree();
        // 
        Node<T>* get_root();
        bool insert( T content );
        Node<T>* find( T content );

        // Pre Order, In Order, Pos Order,
        void pre_order();
        void in_order();
        void pos_order();

        // Function to print tree-like hierarchical structure
        void print_hierarchy();
};

#endif