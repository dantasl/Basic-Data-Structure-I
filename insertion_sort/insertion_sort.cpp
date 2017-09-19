//    Compile: g++ -Wall -std=c++11 insertion_sort.cpp -o insertion_sort

#include <iostream> // cout, endl
#include <iterator> // distance
#include <algorithm> // copy, swap

bool compare( int a, int b ){ return ( a < b ); }

template< typename FwrdIt, typename Compare >
void insertion_sort(FwrdIt _begin, FwrdIt _last, Compare cmp )
{
    auto it = _begin; // points to the beginning of the range
    for(; it != _last; ++it) //iterates over each member to sort
    {
        auto carry = it; //unsorted number of the round
        while( carry != _begin and cmp(*carry, *(carry - 1)) ) //decrements from "it" till beginning of the range
        {
            std::swap( *carry, *(carry-1) );
            carry--;
        }
    }  
}

int main()
{
	int A[] = { 12, 1, 3, 2, 7, 90, 45, 11, 45 };

    // Print original array.
    std::cout << ">>> Original array: ";
    std::copy( std::begin(A), std::end(A),  std::ostream_iterator<int>( std::cout, " " ) );
    std::cout << std::endl;

    // Call insertion sort on the entire array.
    insertion_sort( std::begin(A), std::end(A), compare );

    // Print the result of partition.
    std::cout << ">>> Partitioned array: ";
    std::copy( std::begin(A), std::end(A),  std::ostream_iterator<int>( std::cout, " " ) );
    std::cout << std::endl;

	return 0;
}