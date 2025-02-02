cmake_minimum_required(VERSION 3.30)
project(DataStructuresSeminars CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 23)

if(CMAKE_CXX_COMPILER_ID MATCHES "Clang" AND NOT ANDROID)
    add_compile_options(-stdlib=libc++)
    add_link_options(-stdlib=libc++)
endif()

add_subdirectory(src/SortingAlgorithms)
add_subdirectory(src/DataStructures)
add_subdirectory(test)
