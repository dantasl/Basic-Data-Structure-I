//    Compile: g++ -Wall -std=c++11 quick_sort.cpp -o quick_sort

#include <iostream> // cout, endl
#include <iterator> // distance
#include <algorithm> // copy, swap

bool compare( int a, int b ){ return ( a < b ); }

// finds pivot and creates a range: lesser than pivot goes left and greater goes right.
template< typename FwrdIt, typename Compare >
FwrdIt partition(FwrdIt _begin, FwrdIt _last, Compare cmp)
{
    auto pivot = _last - 1; // pivot, for this algorithm is the last element (right end)
    auto fast = _begin;
    auto slow = _begin; // delimites a range of elements lesser than the pivot
    for(; fast != _last; ++fast) // iterates over each element of the array
    {
        if( cmp(*fast, *pivot) ) // if element is lesser than pivot
        {
            std::swap( *slow, *fast ); // place that element on the left end of pivot
            slow++;
        }   
    }
    std::swap(*slow, *pivot); // place pivot after his immediate lesser value.
    return slow; // returns address of the pivot
}

template< typename FwrdIt, typename Compare >
void quick_sort(FwrdIt _begin, FwrdIt _last, Compare cmp )
{
   if(_begin < _last)
   {
        auto partitioned = partition(_begin, _last, cmp);
        quick_sort(_begin, partitioned, cmp); // apply recursion on left elements of pivot
        quick_sort(partitioned + 1, _last, cmp); //apply recursion on right right elements of pivot        
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
    quick_sort( std::begin(A), std::end(A), compare );

    // Print the result of partition.
    std::cout << ">>> Partitioned array: ";
    std::copy( std::begin(A), std::end(A),  std::ostream_iterator<int>( std::cout, " " ) );
    std::cout << std::endl;

	return 0;
}