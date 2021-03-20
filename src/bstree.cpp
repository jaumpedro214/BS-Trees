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
    if( this->root!=nullptr )
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
//              Remove functions
template <class T>
bool BSTree<T>::remove( T content ){
    // Delete if root
    if( this->root->left == nullptr && this->root->right == nullptr ){
        delete this->root;
        this->root = nullptr;
        this->size--;
        return true;
    }
    return this->remove_at(content, this->root);
}
template <class T>
bool BSTree<T>::remove_at( const T &content, Node<T> *ptr_fat ){
    Node<T> *ptr = nullptr;
    bool removed = false;
    char son_direction = 0;

    if( ptr_fat->content > content ){
        if( ptr_fat->left == nullptr ){
            removed = false;
        }
        else if( ptr_fat->left->content == content ){
            ptr = ptr_fat->left;
            son_direction = -1;
            this->delete_node(ptr_fat, ptr, son_direction);
            removed = true;
        }
        else{ 
            removed = this->remove_at(content, ptr_fat->left);
        }
    }
    else if( ptr_fat->content < content ){
        if( ptr_fat->right == nullptr ){
            removed = false;
        }
        else if( ptr_fat->right->content == content ){
            ptr = ptr_fat->right;
            son_direction = 1;
            this->delete_node(ptr_fat, ptr, son_direction);
            removed = true;
        }
        else{
            removed = this->remove_at(content, ptr_fat->right);
        }
    }
    else{
        ptr = ptr_fat;
        son_direction = 0;
        this->delete_node(nullptr, ptr, son_direction);
    }

    return removed;
}
template <class T>
void BSTree<T>::delete_node( Node<T> *ptr_fat, Node<T> *ptr, char son_direction ){
    Node<T> *ptr_aux = nullptr, *ptr_aux_fat = nullptr;

    // Remove Cases
    //    Leaf Node
    if( ptr->left==nullptr && ptr->right==nullptr  ){
        delete ptr;
        if( son_direction != 0 ){
            if( son_direction == -1 )
                ptr_fat->left = nullptr;
            else
                ptr_fat->right = nullptr;
        }
    }
    else if( ptr->right != nullptr ){
        ptr_aux_fat = ptr->right;//
        ptr_aux = ptr_aux_fat->left;

        if( ptr_aux == nullptr ){
            ptr->content = ptr_aux_fat->content;
            ptr->right = ptr_aux_fat->right;//
            ptr_aux_fat->right = nullptr;//
            delete ptr_aux_fat;
        }
        else{
            while( ptr_aux->left != nullptr ){
                ptr_aux_fat = ptr_aux;
                ptr_aux = ptr_aux->left;
            }
            ptr->content = ptr_aux->content;
            ptr_aux_fat->left = ptr_aux->right;//
            ptr_aux->right = nullptr;//
            delete ptr_aux;
        }
    }
    else if( ptr->left != nullptr ){
        ptr_aux_fat = ptr->left;//
        ptr_aux = ptr_aux_fat->right;

        if( ptr_aux == nullptr ){
            ptr->content = ptr_aux_fat->content;
            ptr->left = ptr_aux_fat->left;//
            ptr_aux_fat->left = nullptr;//
            delete ptr_aux_fat;
        }
        else{
            while( ptr_aux->right != nullptr ){
                ptr_aux_fat = ptr_aux;
                ptr_aux = ptr_aux->right;
            }

            ptr->content = ptr_aux->content;
            ptr_aux_fat->right = ptr_aux->left;//
            ptr_aux->left = nullptr;//
            delete ptr_aux;
        }
    }

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