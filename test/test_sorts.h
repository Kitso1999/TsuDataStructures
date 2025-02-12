#ifndef TEST_SORTS_H
#define TEST_SORTS_H

#include <gtest/gtest.h>
#include <concepts>

template<std::invocable Func>
class TestSort : public ::testing::Test
{
    TestSort(Func &func) : func(func) {}
    TestSort(const Func &func) : func(func) {}

    Func func;
};

#endif //TEST_SORTS_H
