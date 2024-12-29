cmake_minimum_required(VERSION 3.30)
project(DataStructuresSeminars)

set(CMAKE_CXX_STANDARD 20)

add_executable(DataStructuresSeminars main.cpp
        DataStructures/BinarySearchTree/BST.h
        DataStructures/BinarySearchTree/RBT.h
        DataStructures/BinarySearchTree/AVL.h)

add_subdirectory(SortingAlgorithms)
target_link_libraries(DataStructuresSeminars SortingAlgorithms)