include(FetchContent)

FetchContent_Declare(
        GoogleTest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG a866428a78ab02b7072f96c8de15802ffd451a7f
)

FetchContent_MakeAvailable(GoogleTest)

add_executable(test-sorting test_sorts.cpp
        test_sorts.h)
target_link_libraries(test-sorting PRIVATE SortingAlgorithms gtest_main)

include(GoogleTest)
gtest_discover_tests(test-sorting)