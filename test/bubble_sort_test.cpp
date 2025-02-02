#include <list>
#include <deque>
#include <vector>
#include <array>
#include <ranges>

#include <catch2/catch_test_macros.hpp>
#include <SortingAlgorithms.h>

TEST_CASE( "Sorts Empty Containers of type int", "[bubble_sort]" )
{
    std::list<int> l = {};
    std::deque<int> dq = {};
    std::vector<int> v = {};
    std::array<int, 0> arr = {};

    kts::BubbleSort( l.begin(), l.end() );
    REQUIRE( l.empty() );
    kts::BubbleSort( dq.begin(), dq.end() );
    REQUIRE( dq.empty() );
    kts::BubbleSort( v.begin(), v.end() );
    REQUIRE( v.empty() );
    kts::BubbleSort( arr.begin(), arr.end() );
    REQUIRE( arr.empty() );
}

TEST_CASE( "Sorts containers of 1 int", "[bubble_sort]" )
{
    std::list l = { 1 };
    std::deque dq = { 2 };
    std::vector v = { 3 };
    std::array arr = { 4 };

    kts::BubbleSort( l.begin(), l.end() );
    REQUIRE( ( l.size() == 1L && l.front() == 1 ) );
    kts::BubbleSort( dq.begin(), dq.end() );
    REQUIRE( ( dq.size() == 1 && dq.front() == 2 ) );
    kts::BubbleSort( v.begin(), v.end() );
    REQUIRE( ( v.size() == 1 && v.front() == 3 ) );
    kts::BubbleSort( arr.begin(), arr.end() );
    REQUIRE( ( arr.size() == 1 && arr.front() == 4 ) );
}

TEST_CASE( "Sorts containers of 10 ints", "[bubble_sort]" )
{
    static constexpr int initial[] = { 31, 54, 23, 6, 4, 23, 6, 4, 2, 3 };

    std::list l{ std::from_range, initial };
    std::deque dq{ std::from_range, initial };
    std::vector v{ std::from_range, initial };
    std::array<int, std::size( initial )> arr;
    std::ranges::copy( initial, arr.begin() );

    const auto sorted = [] {
        std::vector v( std::from_range, initial );
        std::ranges::sort( v );
        return v;
    }();

    kts::BubbleSort( l.begin(), l.end() );
    REQUIRE( std::ranges::equal( l, sorted ) );

    kts::BubbleSort( dq.begin(), dq.end() );
    REQUIRE( std::ranges::equal( dq, sorted ) );

    kts::BubbleSort( v.begin(), v.end() );
    REQUIRE( std::ranges::equal( v, sorted ) );

    kts::BubbleSort( arr.begin(), arr.end() );
    REQUIRE( std::ranges::equal( arr, sorted ) );
}

TEST_CASE( "Sorts containers of 1000 random ints", "[bubble_sort]" )
{
    std::list<int> l( 1000 );
    std::deque<int> dq( 1000 );
    std::vector<int> v( 1000 );
    std::array<int, 1000> arr;

    std::random_device rd;
    std::default_random_engine rng{ rd() };
    std::uniform_int_distribution dist;

    for (auto &val : l)
        val = dist(rng);

    for (auto &val : dq)
        val = dist(rng);

    for (auto &val : v)
        val = dist(rng);

    for (auto &val : arr)
        val = dist(rng);

    kts::BubbleSort( l.begin(), l.end() );
    REQUIRE( std::ranges::is_sorted(l));

    kts::BubbleSort( dq.begin(), dq.end() );
    REQUIRE( std::ranges::is_sorted(dq));

    kts::BubbleSort( v.begin(), v.end() );
    REQUIRE( std::ranges::is_sorted(v));

    kts::BubbleSort( arr.begin(), arr.end() );
    REQUIRE( std::ranges::is_sorted(arr));
}