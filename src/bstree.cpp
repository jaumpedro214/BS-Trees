#include "bstree.hpp"

// Node Class
//      Constructors & Destructors
template <class T> Node<T>::Node(){};
template <class T> Node<T>::Node(T content){
    this->content = content;
}
template <class T> Node<T>::~Node(){
    if( this->left != nullptr )
        delete this->left;
    if( this->right != nullptr )
        delete this->right;
}
//      Geters & Seters
template <class T> T Node<T>::get_content(){
    return this->content;
}
template <class T> int Node<T>::update_n_null(){
    int prev_n_null_ptr = this->n_null_ptr;
    int n_null_ptr = 0;
    n_null_ptr += this->left == nullptr;
    n_null_ptr += this->right == nullptr;
    this->n_null_ptr = n_null_ptr;
    return (n_null_ptr-prev_n_null_ptr);
}
//      Other methods
template <class T> bool Node<T>::update_height(){
    int prev_height = this->height;

    if( this->left == nullptr && this->right == nullptr )
        this->height = 0;
    else if( this->right == nullptr )
        this->height = this->left->height+1;
    else if( this->left == nullptr )
        this->height = this->right->height+1;
    else
        this->height = std::max(this->left->height, this->right->height)+1;

    // Returne true if the node's height has changed
    return !( prev_height == this->height );
}
template <class T> bool Node<T>::update_n_nodes(){
    int prev_left = this->n_left_nodes, prev_right = this->n_right_nodes;

    if( this->left == nullptr )
        this->n_left_nodes = 0;
    else
        this->n_left_nodes = 1+this->left->n_left_nodes+this->left->n_right_nodes;

    if( this->right == nullptr )
        this->n_right_nodes = 0;
    else
        this->n_right_nodes = 1+this->right->n_left_nodes+this->right->n_right_nodes;

    return !( prev_left == this->n_left_nodes && prev_right == this->n_right_nodes);
}
template <class T> bool Node<T>::update_level( int level ){
    int prev_level = this->level;
    this->level = level;
    return !(prev_level == level);
}
template <class T>
bool Node<T>::is_full(){
    int n_nodes = this->n_left_nodes + this->n_right_nodes+1+1;
    bool is_power_of_2;
    bool has_min_height;
    float log2_result = log2( n_nodes );
    float log2_result_floor = floor( log2_result );

    // If a tree has 2 or less nodes, its always full 
    if( n_nodes <= 2 ) return true;

    // check if the number of nodes+1 is a power of 2
    is_power_of_2 = abs( log2_result_floor - log2_result ) < 0.00001;
    // check if the tree has min height
    has_min_height = this->height == log2_result_floor - 1;
    return is_power_of_2 && has_min_height;
}
template <class T>
bool Node<T>::update_is_complete(){
    bool prev_is_complete = this->is_complete;
    int left_height, right_height;
    bool left_is_full, right_is_full;
    bool left_is_complete, right_is_complete;

    if( this->left == nullptr ){
        left_height = -1;
        left_is_full = true;
        left_is_complete = true;
    }
    else{
        left_height = this->left->height;
        left_is_full = this->left->is_full();
        left_is_complete = this->left->is_complete;
    }

    if( this->right == nullptr ){
        right_height = -1;
        right_is_full = true;
        right_is_complete = true;
    }
    else{
        right_height = this->right->height;
        right_is_full = this->right->is_full();
        right_is_complete = this->right->is_complete;
    }

    if( left_is_complete && right_is_complete ){
        if( left_is_full || right_is_full ){
            this->is_complete = (abs( left_height - right_height ) <= 1);
        }
        else{
            this->is_complete = (left_height == right_height);
        }
    }

    return this->is_complete==prev_is_complete;
}

// BSTree Class
//      Constructors & Destructors
template <class T> 
BSTree<T>::~BSTree(){
    if( this->root!=nullptr )
        delete this->root;
}

//      Geters & Seters
template <class T> 
Node<T>* BSTree<T>::get_root(){
    return this->root;
}
template <class T> 
int BSTree<T>::get_size(){
    return this->size;
}

//      Other Methods

//      Insert, Remove & Find
template <class T> 
bool BSTree<T>::insert( T content ){
    Node<T> *no = new Node<T>(content);

    // Create root if tree is empty
    if( this->size == 0 ){
        this->root = no;
        this->size++;
        this->update_path( content, this->root, 0 );
        return true;
    }
    // Insert new node at the correct position
    if( this->insert_at( content, this->root ) ){
        this->size++;
        this->update_path( content, this->root, 0 );
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

    return inserted == -1 || inserted == 1;
}

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

//     Remove functions
template <class T>
bool BSTree<T>::remove( T content ){
    bool r_value;

    // Delete if root
    if( this->root->left == nullptr && this->root->right == nullptr ){
        delete this->root;
        this->root = nullptr;
        this->size--;
        return true;
    }
    r_value = this->remove_at(content, this->root);

    if( r_value ){
        this->size--;
    }
    return r_value;
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
        removed = true;
        this->delete_node(nullptr, ptr, son_direction);
    }

    return removed;
}
template <class T>
void BSTree<T>::delete_node( Node<T> *ptr_fat, Node<T> *ptr, char son_direction ){
    Node<T> *ptr_aux = nullptr, *ptr_aux_fat = nullptr;
    T content_update_path;

    // Remove Cases
    //    Leaf Node
    if( ptr->left==nullptr && ptr->right==nullptr  ){
        // Update Path
        content_update_path = ptr->content;

        delete ptr;
        if( son_direction != 0 ){
            if( son_direction == -1 )
                ptr_fat->left = nullptr;
            else
                ptr_fat->right = nullptr;
        }
    }//   Node with left subtree empty
    else if( ptr->left == nullptr ){
        ptr_aux_fat = ptr->right;//
        ptr_aux = ptr_aux_fat->left;

        if( ptr_aux == nullptr ){
            ptr->content = ptr_aux_fat->content;
            ptr->right = ptr_aux_fat->right;//
            ptr_aux_fat->right = nullptr;//
            delete ptr_aux_fat;

            content_update_path = ptr->content;
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

            content_update_path = ptr_aux_fat->content;
        }
    }//   Node with left subtree not empty
    else if( ptr->left != nullptr ){
        ptr_aux_fat = ptr->left;//
        ptr_aux = ptr_aux_fat->right;

        if( ptr_aux == nullptr ){
            ptr->content = ptr_aux_fat->content;
            ptr->left = ptr_aux_fat->left;//
            ptr_aux_fat->left = nullptr;//
            delete ptr_aux_fat;

            content_update_path = ptr->content;
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

            content_update_path = ptr_aux_fat->content;
        }
    }

    //Update path
    this->update_path( content_update_path, this->root, 0 );
}

// Function to update nodes info only in a especific path
template <class T>
void BSTree<T>::update_path( const T &content, Node<T> *ptr, int level ){
    
    if( ptr == nullptr )
        return;

    if( ptr->content > content )
        this->update_path(content, ptr->left, level+1);
    else if( ptr->content < content )
        this->update_path(content, ptr->right, level+1);

    ptr->update_height();
    ptr->update_n_nodes();
    ptr->update_level(level);
    ptr->update_is_complete();

    // Update null_ptr_per_level vector
    // Useful for is_complete() and is_full()
}
// Pre Order, In Order, Pos Order,
template <class T>
void BSTree<T>::pre_order(){
    this->pre_order(this->root);
}
template <class T>
void BSTree<T>::pre_order(Node<T> *root){
    if( root == nullptr ){
        return;
    };
    std::cout << root->get_content() <<" ";
    pre_order(root->left);
    pre_order(root->right);
}

template <class T>
void BSTree<T>::in_order(){
    this->in_order(this->root);
}
template <class T>
void BSTree<T>::in_order(Node<T> *root){
    if( root == nullptr ){
        return;
    };
    in_order(root->left);
    std::cout << root->get_content() <<" ";
    in_order(root->right);
}

template <class T>
void BSTree<T>::pos_order(){
    this->pos_order(this->root);
}
template <class T>
void BSTree<T>::pos_order(Node<T> *root){
    if( root == nullptr ){
        return;
    };
    pos_order(root->left);
    pos_order(root->right);
    std::cout << root->get_content() <<" ";
}

template <class T>
void BSTree<T>::print_hierarchy(){
    this->print_hierarchy(this->root, "");
}
template <class T>
void BSTree<T>::print_hierarchy(Node<T> *root, std::string s ){
    if( root == nullptr )
        return;

    print_hierarchy(root->left, s+"  ");
    std::cout << s << root->get_content();
    std::cout << std::endl;
    print_hierarchy(root->right, s+"  ");
}

// Extended Methods:
//       Return nth-element in symmetric order
template <class T>
T BSTree<T>::nth_elem(int pos){
    return this->nth_elem( std::min(pos, this->size), 0, this->root );
}
template <class T>
T BSTree<T>::nth_elem(int pos, int num_left_nodes, Node<T> *ptr){
    
    if( ptr->n_left_nodes + num_left_nodes > pos ){
        return this->nth_elem( pos, num_left_nodes, ptr->left );
    }
    else if( ptr->n_left_nodes + num_left_nodes < pos ){
        return this->nth_elem( pos, ptr->n_left_nodes+1+num_left_nodes, ptr->right );
    }
    return ptr->content;
}
//        Return the position of a element
template <class T>
int BSTree<T>::position( const T &content ){
    return this->position( content, 0, this->root );
}
template <class T>
int BSTree<T>::position( const T &content, int num_left_nodes, Node<T> *ptr ){
    // Return -1 if element is not found
    if( ptr == nullptr )
        return -1;

    if( ptr->content > content ){
        return this->position( content, num_left_nodes, ptr->left );
    }
    else if( ptr->content < content ){
        return this->position( content, ptr->n_left_nodes+1+num_left_nodes, ptr->right );
    }
    return ptr->n_left_nodes + num_left_nodes ;
}
//       Return the Median
template <class T>
T BSTree<T>::median(){
    int p1 = (this->size-1)/2, p2 = (this->size-1)/2 + 1;
    
    if( this->size%2 == 0 ){
        return std::min( this->nth_elem(p1), this->nth_elem(p2) );
    }
    else{
        return this->nth_elem(p1);
    }
}
//       Return whether the tree is Complete
template <class T>
bool BSTree<T>::is_complete(){
    if( this->root == nullptr ) 
        return true;
    return this->root->is_complete;
}
//       Return whether the tree is Full
template <class T>
bool BSTree<T>::is_full(){
    if( this->root == nullptr ) 
        return true;
    return this->root->is_full();
}
//      Return a string representing the tree by level
template <class T>
std::string BSTree<T>::to_string(){
    std::queue< Node<T>* > node_queue;
    Node<T> *no_atual;
    std::stringstream ss;

    if( this->root == nullptr )
        return "";
    
    node_queue.push( this->root );
    while( !node_queue.empty() ){
        no_atual = node_queue.front();
        node_queue.pop();
        ss << no_atual->content << " ";

        if( no_atual->left != nullptr )
            node_queue.push( no_atual->left );
        if( no_atual->right != nullptr )
            node_queue.push( no_atual->right );
    }
    return ss.str();
}