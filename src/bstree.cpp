#include "bstree.hpp"
#include <iostream>


// Node Class
//      Constructors & Destructors
template <class T> Node<T>::Node(){};
template <class T> Node<T>::Node(T content){
    this->content = content;
};
template <class T> Node<T>::~Node(){
    if( this->left != nullptr )
        delete this->left;
    if( this->right != nullptr )
        delete this->right;
};
//      Geters & Seters
template <class T> T Node<T>::get_content(){
    return this->content;
};

// BSTree Class
//      Constructors & Destructors
template <class T> 
BSTree<T>::~BSTree(){
    delete this->root;
};

//      Geters & Seters
template <class T> 
Node<T>* BSTree<T>::get_root(){
    return this->root;
};

//      Insert & Remove
template <class T> 
bool BSTree<T>::insert( T content ){
    Node<T> *no = new Node<T>(content);

    // Create root if tree is empty
    if( this->size == 0 ){
        this->root = no;
        this->size++;
        return true;
    }
    // Insert new nod at the correct position
    if( this->insert_at( content, this->root ) ){
        this->size++;
    }
    else return false;

    delete no;
    return true;
};

template <class T>
bool BSTree<T>::insert_at( const T &content, Node<T> *ptr ){
    
    if( ptr->get_content() == content ){
        return false;
    }
    else if( ptr->get_content() > content ){
        if( ptr->left == nullptr ){
            ptr->left = new Node<T>(content);
            return true;
        }
        else{
            return insert_at(content, ptr->left);
        }
    }
    else if( ptr->get_content() < content ){
        if( ptr->right == nullptr ){
            ptr->right = new Node<T>(content);
            return true;
        }
        else{
            return insert_at(content, ptr->right);
        }
    }

    return true;
};