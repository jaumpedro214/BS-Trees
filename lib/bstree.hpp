#ifndef BSTREE_HPP
#define BSTREE_HPP

#include <iostream>
#include <string>
#include <algorithm> // max
#include <vector> // vector null_ptr_per_level
#include <queue> // needed to to_string() method
#include <sstream>

#include <math.h> 

template <class T>
class Node{
    template<class U> friend class BSTree;
    private:
        T content;
        int height = 0;
        int level = 0;
        int n_left_nodes = 0, n_right_nodes = 0;
        bool is_complete = true;
        Node<T> *left=nullptr, *right=nullptr;
    public:
        // Constructors & Destructors
        Node();
        Node(T content);
        ~Node();
        // Getters & Setters
        T get_content();
        // Update parameters
        bool update_height();
        bool update_n_nodes();
        bool update_level( int level );
        bool update_is_complete();
        bool is_full();
};

template <class T = int> 
class BSTree{
    private:
        //Parameters
        Node<T> *root=nullptr;
        int altura = 0;
        int size = 0;

        // Insert, Remove & Find - Utils
        bool insert_at( const T &content, Node<T> *ptr );
        bool remove_at( const T &content, Node<T> *ptr_fat );
        void delete_node( Node<T> *ptr_fat, Node<T> *ptr, char son_direction );
        Node<T>* find_at(const T &content, Node<T> *ptr);
        int update_nodes( Node<T> *ptr );
        void update_path( const T &content, Node<T> *ptr, int level );

        // Pre Order, In Order, Pos Order - Overload
        void pre_order(Node<T> *root);
        void in_order(Node<T> *root);
        void pos_order(Node<T> *root);

        // Print hierarchy 
        void print_hierarchy(Node<T> *root, std::string s);

        // Extended Methods - Overload
        T nth_elem(int pos, int num_left_nodes, Node<T> *ptr);
        int position( const T &content, int num_left_nodes, Node<T> *ptr );
    public:
        // Constructors & Destructors
        ~BSTree();

        // Getters & Setters 
        Node<T>* get_root();
        int get_size();

        // Basic Methods: Insert, Remove & Find
        bool insert( T content );
        bool remove( T content );
        Node<T>* find( T content );

        // Pre Order, In Order, Pos Order,
        void pre_order();
        void in_order();
        void pos_order();

        // Function to print tree-like hierarchical structure
        void print_hierarchy();

        // Extended Methods:
        // Return nth-element in symmetric order
        T nth_elem(int pos);
        // Return the position of a element
        int position( const T &content );
        // Return the median
        T median();
        // Return whether the tree is Complete
        bool is_complete();
        // Return whether the tree is Full
        bool is_full();
        // Return a string representing the tree by level
        std::string to_string();
};

#endif