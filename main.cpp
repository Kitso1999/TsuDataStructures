#include <iostream>
#include <SortingAlgorithms.h>
#include <AVL.h>

template<class Rng>
void print( Rng &range );

int main()
{
    AVL<int> bst;

    bst.insert( 10 );
    bst.insert( 40 );
    bst.insert( 20 );
    bst.insert( 30 );
    bst.insert( 40 );
    bst.insert( 50 );


    std::cout << "BST 1" << std::endl;
    std::cout << "Inorder: ";
    bst.inorder();
    std::cout << std::endl;

    std::cout << "Preorder: ";
    bst.preorder();
    std::cout << std::endl;

    std::cout << "Postorder: ";
    bst.postorder();
    std::cout << std::endl;

    auto bst2{ bst };

    std::cout << "BST 2" << std::endl;

    std::cout << "Inorder: ";
    bst2.inorder();
    std::cout << std::endl;

    std::cout << "Preorder: ";
    bst2.preorder();
    std::cout << std::endl;

    std::cout << "Postorder: ";
    bst2.postorder();
    std::cout << std::endl;
}

template<class Rng>
void print( Rng &range )
{
    for ( const auto &item : range )
        std::cout << item << " ";
    std::cout << std::endl;
}