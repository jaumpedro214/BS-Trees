#include "bstree.hpp"


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

//      Insert, Remove & Find
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
    
    char inserted = 0;
    if( ptr->get_content() == content ){
        return false;
    }
    else if( ptr->get_content() > content ){
        if( ptr->left == nullptr ){
            ptr->left = new Node<T>(content);
            inserted = -1;
        }
        else{
            if( insert_at(content, ptr->left) )
                inserted = -1;
        }
    }
    else if( ptr->get_content() < content ){
        if( ptr->right == nullptr ){
            ptr->right = new Node<T>(content);
            inserted = 1;
        }
        else{
            if( insert_at(content, ptr->right) )
                inserted = 1;
        }
    }

    // Updating tree height
    if( inserted == -1 || inserted == 1 ){
        if( ptr->right == nullptr )
            ptr->height = ptr->left->height+1;
        else if( ptr->left == nullptr )
            ptr->height = ptr->right->height+1;
        else
            ptr->height = std::max(ptr->left->height, ptr->right->height)+1;
        return true;
    }

    return false;
};

template <class T>
Node<T>* BSTree<T>::find( T content ){
    
    if( this->root == nullptr )
        return nullptr;

    return this->find_at(content, this->root);
}
template <class T>
Node<T>* BSTree<T>::find_at( const T &content, Node<T> *ptr){
    
    if( ptr == nullptr )
        return nullptr;
    
    if( ptr->content > content )
        return this->find_at(content, ptr->left);
    else if( ptr->content < content )
        return this->find_at(content, ptr->right);
    
    return ptr;
}


// Pre Order, In Order, Pos Order,
template <class T>
void BSTree<T>::pre_order(){
    this->pre_order(this->root);
};
template <class T>
void BSTree<T>::pre_order(Node<T> *root){
    if( root == nullptr ){
        return;
    };
    std::cout << root->get_content() <<" ";
    pre_order(root->left);
    pre_order(root->right);
};

template <class T>
void BSTree<T>::in_order(){
    this->in_order(this->root);
};
template <class T>
void BSTree<T>::in_order(Node<T> *root){
    if( root == nullptr ){
        return;
    };
    in_order(root->left);
    std::cout << root->get_content() <<" ";
    in_order(root->right);
};

template <class T>
void BSTree<T>::pos_order(){
    this->pos_order(this->root);
};
template <class T>
void BSTree<T>::pos_order(Node<T> *root){
    if( root == nullptr ){
        return;
    };
    pos_order(root->left);
    pos_order(root->right);
    std::cout << root->get_content() <<" ";
};

template <class T>
void BSTree<T>::print_hierarchy(){
    this->print_hierarchy(this->root, "");
};
template <class T>
void BSTree<T>::print_hierarchy(Node<T> *root, std::string s ){
    if( root == nullptr ){
        return;
    };
    print_hierarchy(root->left, s+"  ");
    std::cout << s << root->get_content() <<"("<<root->height<< ")\n";
    print_hierarchy(root->right, s+"  ");
};