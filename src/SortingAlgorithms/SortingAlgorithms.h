#ifndef KTS_SORTINGALGORITHMS_H_
#define KTS_SORTINGALGORITHMS_H_

#include <algorithm>
#include <random>
#include <concepts>
#include <iterator>

namespace kts
{

template<std::bidirectional_iterator Iter, std::sentinel_for<Iter> Sent,
         std::predicate<std::iter_value_t<Iter>, std::iter_value_t<Iter>> Pred>
void BubbleSort( Iter first, Sent last, Pred pred )
{
    for ( ; first != last; --last ) {
        bool swapped = false;

        for ( auto left = first, right = std::next( left ); right != last;
              ++left, ++right )
            if ( pred( *right, *left ) ) {
                std::iter_swap( left, right );
                swapped = true;
            }

        if ( !swapped )
            break;
    }
}

template<std::bidirectional_iterator Iter, std::sentinel_for<Iter> Sent>
void BubbleSort( Iter first, Sent last )
{
    BubbleSort(first, last, std::less{} );
}

template<std::forward_iterator Iter, std::sentinel_for<Iter> Sent,
         std::predicate<std::iter_value_t<Iter>, std::iter_value_t<Iter>> Pred>
void SelectionSort( Iter first, Sent last, Pred pred )
{
    for ( ; first != last; ++first ) {
        auto min = std::min_element( first, last, pred );
        std::iter_swap( first, min );
    }
}

template<std::forward_iterator Iter, std::sentinel_for<Iter> Sent>
void SelectionSort( Iter first, Sent last )
{
    SelectionSort(first, last, std::less{} );
}

template<std::bidirectional_iterator Iter, std::sentinel_for<Iter> Sent,
         std::predicate<std::iter_value_t<Iter>, std::iter_value_t<Iter>> Pred>
void InsertionSort( Iter first, Sent last, Pred pred )
{
    auto r_last = std::make_reverse_iterator( first );

    for ( auto next = first; next != last; ++next )
        for ( auto walker = std::make_reverse_iterator( next );
              walker != first && pred( walker, std::next( walker ) ); ++walker )
            std::iter_swap( walker, std::next( walker ) );
}

template<std::bidirectional_iterator Iter, std::sentinel_for<Iter> Sent>
void InsertionSort( Iter first, Sent last )
{
    InsertionSort(first, last, std::less{} );
}

template<std::input_iterator Iter, std::sentinel_for<Iter> Sent,
         std::output_iterator<std::iter_value_t<Iter>> DestIter,
         std::predicate<std::iter_value_t<Iter>, std::iter_value_t<Iter>> Pred>
static void Merge( Iter first_l, Sent last_l, Iter first_r, Sent last_r,
                   DestIter dest, Pred pred )
{
    while ( first_l != last_l && first_r != last_r )
        *dest++ = pred( *first_r, *first_l ) ? *first_r++ : *first_l++;

    while ( first_l != last_l )
        *dest++ = *first_l++;

    while ( first_r != last_r )
        *dest++ = *first_r++;
}

template<std::input_iterator Iter, std::sentinel_for<Iter> Sent,
         std::output_iterator<std::iter_value_t<Iter>> DestIter>
static void Merge( Iter first_l, Sent last_l, Iter first_r, Sent last_r,
                   DestIter dest )
{
    Merge(first_l, last_l, first_r, last_r, dest, std::less{} );
}

template<std::random_access_iterator Iter, std::sentinel_for<Iter> Sent,
         std::predicate<std::iter_value_t<Iter>, std::iter_value_t<Iter>> Pred>
void MergeSort( Iter first, Sent last, Pred pred )
{
    if ( last <= first )
        return;

    auto size = std::distance( first, last );

    auto first_l = std::make_move_iterator( first );
    auto last_l = std::make_move_iterator( first + size / 2 );
    auto first_r = std::make_move_iterator( last_l );
    auto last_r = std::make_move_iterator( last );

    MergeSort( first_l, last_l );
    MergeSort( first_r, last_r );

    std::vector<std::iter_value_t<Iter>> temp;
    temp.reserve( size );

    Merge( first_l, last_l, first_r, last_l, std::back_inserter( temp ), pred );

    std::move( temp.begin(), temp.end() + size, first );
}

template<std::random_access_iterator Iter, std::sentinel_for<Iter> Sent>
void MergeSort( Iter first, Sent last )
{
    MergeSort(first, last, std::less{} );
}

template<std::bidirectional_iterator Iter, std::sentinel_for<Iter> Sent,
    std::predicate<std::iter_value_t<Iter>, std::iter_value_t<Iter>> Pred>
static Iter Partition( Iter first, Sent last, Pred pred )
{
    if ( first == last )
        return last;

    auto pivot = *first;

    // same as while(true)
    for ( ;; ) {
        // skip in-place elements at the beginning
        for ( ;; ) {
            if ( first == last )
                return first;

            if ( !pred( *first, pivot ) )
                break;

            ++first;
        }

        // skip in-place elements at the end
        do {
            --last;

            if ( first == last )
                return last;
        } while ( !pred( *last, pivot) );

        std::iter_swap( first, last ); // swap out-of-place elements
        ++first;                         // advance and loop
    }
}

template<std::bidirectional_iterator Iter, std::sentinel_for<Iter> Sent>
static Iter Partition( Iter first, Sent last )
{
    return Partition( first, last, std::less{} );
}

template<std::bidirectional_iterator Iter, std::sentinel_for<Iter> Sent,
        std::predicate<std::iter_value_t<Iter>, std::iter_value_t<Iter>> Pred>
void QuickSort( Iter first, Sent last, Pred pred )
{
    if (first == last)
        return;

    auto partition_point = Partition( first, last, pred );
    std::iter_swap( first, partition_point );

    QuickSort( first, partition_point );
    QuickSort( std::next(partition_point), last );
}

// ***TODO implement with templates vvv
// static void heapify( int *arr, int size, int i )
// {
//     int l = 2 * i + 1;
//     int r = 2 * i + 2;
//
//     int largest = i;
//     if ( l < size && arr[largest] < arr[l] )
//         largest = l;
//     if ( r < size && arr[largest] < arr[r] )
//         largest = r;
//
//     if ( largest != i ) {
//         std::swap( arr[i], arr[largest] );
//         heapify( arr, size, largest );
//     }
// }
//
// static void push_heap( int *arr, int size )
// {
//     for ( int i = size; i > 0 && arr[i / 2] < arr[i]; i /= 2 )
//         std::swap( arr[i / 2], arr[i] );
// }
//
// static void pop_heap( int *arr, int size )
// {
//     std::swap( arr[0], arr[size - 1] );
//     heapify( arr, size - 1, 0 );
// }
//
// static void make_heap( int *arr, int size )
// {
//     for ( int i = ( size - 1 ) / 2; i >= 0; i-- )
//         heapify( arr, size, i );
// }
//
// void HeapSort( int *arr, int size )
// {
//     make_heap( arr, size );
//     while ( size > 1 )
//         pop_heap( arr, size-- );
// }
//***

}

#endif // KTS_SORTINGALGORITHMS_H_
