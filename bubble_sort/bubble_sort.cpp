//    Compile: g++ -Wall -std=c++11 bubble_sort.cpp -o bubble_sort

#include <iostream> // cout, endl
#include <iterator> // distance
#include <algorithm> // copy, swap

bool compare( int a, int b ){ return ( a < b ); }

template< typename FwrdIt, typename Compare >
void bubble_sort(FwrdIt _begin, FwrdIt _last, Compare cmp )
{
    auto it = _begin;
    while(true)
    {
        bool continue_bubble = false; // if this values stays false at the end of the loop, means that array is sorted.
        for(it = _begin; it != _last - 1; ++it) // ALERT! note that this is it < _last - 1. if we go over this, the comp will grab garbage
        {
            if( cmp( *(it + 1), *it ) ) // compares if the next element is lesser than the current
            {
                std::swap( *(it + 1), *it );
                continue_bubble = true; // indicates that ocurred at least one swap between elements
            }
        }
        if(!continue_bubble) // if no elements were swapped, means that every element is already sorted.
            break;   
    }    
}

int main()
{
	int A[] = { 12, 1, 3, 2, 7, 90, 45, 11, 45 };
    //int A[] = { 1, 2, 3, 4, 5, 6, 7 };

    // Print original array.
    std::cout << ">>> Original array: ";
    std::copy( std::begin(A), std::end(A),  std::ostream_iterator<int>( std::cout, " " ) );
    std::cout << std::endl;

    // Call insertion sort on the entire array.
    bubble_sort( std::begin(A), std::end(A), compare );

    // Print the result of partition.
    std::cout << ">>> Partitioned array: ";
    std::copy( std::begin(A), std::end(A),  std::ostream_iterator<int>( std::cout, " " ) );
    std::cout << std::endl;

	return 0;
}