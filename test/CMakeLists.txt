include(FetchContent)

FetchContent_Declare(
        Catch2
        GIT_REPOSITORY https://github.com/catchorg/Catch2.git
        GIT_TAG 914aeecfe23b1e16af6ea675a4fb5dbd5a5b8d0a # v3.8.0
        FIND_PACKAGE_ARGS NAMES Catch2
)

FetchContent_MakeAvailable(Catch2)

add_executable(test-sorting bubble_sort_test.cpp)
target_link_libraries(test-sorting PRIVATE SortingAlgorithms Catch2::Catch2WithMain)
include(CTest)

list(APPEND CMAKE_MODULE_PATH ${catch2_SOURCE_DIR}/extras)
include(Catch)
catch_discover_tests(test-sorting)