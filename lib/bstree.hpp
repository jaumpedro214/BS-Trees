#ifndef BSTREE_HPP
#define BSTREE_HPP

template <class T>
class Node{
    template<class U> friend class BSTree;
    private:
        T content;
        int level = 0;
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
    public:
        ~BSTree();

        Node<T>* get_root();
        bool insert( T content );
};

#endif