/*
    Compile: g++ -Wall -std=c++11 selection_sort.cpp -o selection_sort
    Selection sort is always trying to find the minimum value, and swaps.
*/

#include <iostream> // cout, endl
#include <iterator> // distance
#include <algorithm> // copy, swap

bool compare( int a, int b ){ return ( a < b ); }

template< typename FwrdIt, typename Compare >
void selection_sort(FwrdIt _begin, FwrdIt _last, Compare cmp )
{
    auto it = _begin; // points to the beginning of the range
    auto j = _begin;
    for(; it != _last; ++it) //iterates over each member to sort
    {
        auto current_minimum = it;
        for(j = it; j != _last; ++j)
        {
            if( cmp( *j, *current_minimum ) )
                current_minimum = j; 
        }
        std::swap(*it, *current_minimum);    
    }  
}

int main()
{
	int A[] = { 12, 1, 3, 2, 7, 90, 45, 11, 45 };
    //int A[] = { 1, 2, 3, 4, 5, 6, 7, 3, 3, 3, 3 };

    // Print original array.
    std::cout << ">>> Original array: ";
    std::copy( std::begin(A), std::end(A),  std::ostream_iterator<int>( std::cout, " " ) );
    std::cout << std::endl;

    // Call insertion sort on the entire array.
    selection_sort( std::begin(A), std::end(A), compare );

    // Print the result of partition.
    std::cout << ">>> Partitioned array: ";
    std::copy( std::begin(A), std::end(A),  std::ostream_iterator<int>( std::cout, " " ) );
    std::cout << std::endl;

	return 0;
}