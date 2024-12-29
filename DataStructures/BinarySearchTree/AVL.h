#ifndef AVL_H
#define AVL_H

#include <cassert>
#include <iostream>
#include <memory>

// recursive implementation
template<class T>
class AVL
{
private:
    struct Node
    {
        T value;
        int height{ 1 };
        Node *left{};
        Node *right{};
    };

public:
    AVL() = default;
    AVL( const AVL &other );
    AVL &operator=( const AVL &other );
    ~AVL();

    void insert( const T &value );
    bool search( const T &value );
    void erase( const T &value );

    void inorder( std::ostream &out = std::cout ) const;
    void preorder( std::ostream &out = std::cout ) const;
    void postorder( std::ostream &out = std::cout ) const;

private:
    Node *copy_subtree( Node *other_root );
    void destroy_substree( Node *root );

    Node *rotate_left( Node *root );
    Node *rotate_right( Node *root );

    Node *get_successor( Node *root );

    static int height( Node *node ) { return node ? node->height : 0; }
    static int get_balance_factor( Node *node )
    {
        return height( node->left ) - height( node->right );
    }

    Node *insert( const T &value, Node *root );
    Node *search( const T &value, Node *root );
    Node *erase( const T &value, Node *root );

    void inorder( Node *root, std::ostream &out ) const;
    void preorder( Node *root, std::ostream &out ) const;
    void postorder( Node *root, std::ostream &out ) const;

private:
    Node *root_{};
};

template<class T>
AVL<T>::AVL( const AVL &other )
{
    root_ = copy_subtree( other.root_ );
}

template<class T>
AVL<T> &AVL<T>::operator=( const AVL &other )
{
    if ( this != &other ) {
        std::destroy_at( this );
        std::construct_at( this, other );
    }

    return *this;
}

template<class T>
AVL<T>::~AVL()
{
    destroy_substree( root_ );
}

template<class T>
void AVL<T>::insert( const T &value )
{
    root_ = insert( value, root_ );
}

template<class T>
bool AVL<T>::search( const T &value )
{
    return search( value, root_ );
}

template<class T>
typename AVL<T>::Node *AVL<T>::copy_subtree( Node *other_root )
{
    if ( !other_root )
        return nullptr;

    auto *my_root = new Node{ other_root->value };
    my_root->left = copy_subtree( other_root->left );
    my_root->right = copy_subtree( other_root->right );

    return my_root;
}

template<class T>
void AVL<T>::destroy_substree( Node *root )
{
    if ( !root )
        return;

    destroy_substree( root->left );
    destroy_substree( root->right );
    delete root;
}

template<class T>
typename AVL<T>::Node *AVL<T>::rotate_left( Node *root )
{
    Node *new_root = root->right;

    root->right = new_root->left;
    new_root->left = root;

    return new_root;
}

template<class T>
typename AVL<T>::Node *AVL<T>::rotate_right( Node *root )
{
    Node *new_root = root->left;

    root->left = new_root->right;
    new_root->right = root;

    return new_root;
}

template<class T>
typename AVL<T>::Node *AVL<T>::get_successor( Node *root )
{
    assert( !root );

    auto *succ = root->right;
    while ( succ->left )
        succ = succ->left;

    return succ;
}

template<class T>
typename AVL<T>::Node *AVL<T>::insert( const T &value, Node *root )
{
    if ( !root )
        return new Node{ value };

    if ( value < root->value )
        root->left = insert( value, root->left );
    else if ( root->value < value )
        root->right = insert( value, root->right );

    root->height = std::max( height( root->left ), height( root->right ) ) + 1;

    int balance_factor = get_balance_factor( root );

    if ( balance_factor > 1 ) { // L_
        if ( value < root->left->value ) // LL
            root->left = rotate_left( root->left );
        root = rotate_right( root ); // LL || LR
    } else if ( balance_factor < -1 ) { // R_
        if ( root->right->value < value ) // RR
            root->right = rotate_right( root->right );
        root = rotate_left( root );
    }

    return root;
}

template<class T>
typename AVL<T>::Node *AVL<T>::search( const T &value, Node *root )
{
    if ( !root )
        return nullptr;

    if ( value < root->value )
        return search( value, root->left );
    if ( root->value < value )
        return search( value, root->right );
    return root;
}

template<class T>
void AVL<T>::erase( const T &value )
{
    root_ = erase( value, root_ );
}

template<class T>
typename AVL<T>::Node *AVL<T>::erase( const T &value, Node *root )
{
    if ( !root )
        return nullptr;

    if ( value < root->value )
        root->left = erase( value, root->left );
    else if ( root->value < value )
        root->right = erase( value, root->right );
    else {
        if ( root->left && root->right ) {
            auto *succ = get_successor( root->left );
            root->value = succ->value;
            root->right = erase( succ->value, root->right );
        } else {
            auto *child = root->right ? root->right : root->left;
            delete root;

            root = child;
        }
    }

    root->height = std::max( height( root->left ), height( root->right ) ) + 1;

    int balance_factor = get_balance_factor( root );

    if ( balance_factor > 1 ) { // L_
        if ( value < root->left->value ) // LL
            root->left = rotate_left( root->left );
        root = rotate_right( root ); // LL || LR
    } else if ( balance_factor < -1 ) { // R_
        if ( root->right->value < value ) // RR
            root->right = rotate_right( root->right );
        root = rotate_left( root );
    }

    return root;
}

template<typename T>
void AVL<T>::inorder( std::ostream &out ) const
{
    inorder( root_, out );
}
template<class T>
void AVL<T>::preorder( std::ostream &out ) const
{
    preorder( root_, out );
}
template<class T>
void AVL<T>::postorder( std::ostream &out ) const
{
    postorder( root_, out );
}

template<typename T>
void AVL<T>::inorder( Node *root, std::ostream &out ) const
{
    if ( root ) {
        inorder( root->left );
        out << root->value << " ";
        inorder( root->right );
    }
}

template<typename T>
void AVL<T>::preorder( Node *root, std::ostream &out ) const
{
    if ( root ) {
        inorder( root->left );
        out << root->value << " ";
        inorder( root->right );
    }
}

template<typename T>
void AVL<T>::postorder( Node *root, std::ostream &out ) const
{
    if ( root ) {
        inorder( root->left );
        out << root->value << " ";
        inorder( root->right );
    }
}
#endif // AVL_H
