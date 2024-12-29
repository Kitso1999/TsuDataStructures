#include <iostream>
#include <SortingAlgorithms.h>

template<class Rng>
void print(Rng &range);

int main()
{
    int arr[] = {4,5,3,2,1,5,9,10};
    int size = sizeof(arr) / sizeof(arr[0]);
    HeapSort(arr, size);
    print(arr);
}

template<class Rng>
void print(Rng &range)
{
    for (const auto &item : range)
        std::cout << item << " ";
    std::cout << std::endl;
}