/**
 * @file binary_search.cpp
 *		g++ -Wall -std=c++11 binary_search.cpp -o binary_search
 *		You need to know your range (where to begin and end) and which value you're searching (var x).
 *		The binary search is basicly divided in three variables: one to represent where is your
 *		left, other for the right and the last one for the mid. At the first iteration, the left
 *		is where the array begin and the right is where it ends. 
 * 
 *		After declaring those first values, you can now enter the loop. When your left and right values
 *		are the same, but they're not equal x, x ain't in the array.
 *
 * 		To calculate the mid you can use this formula: left + (right - left)/2.
 *	
 *		If the mid is greater than x, then x may be on the right half. If mid is lesser than x, then it may
 *		be on the left half.
 *
 *		Eventually, if x is inside the array, the mid will be equal to it.
 *
 *		In this file you will find both iterative and recursive versions.
 * @author Lucas Gomes Dantas
 * @date September 13th, 2017
 */

#include <iostream>
#include <iterator>
#include <algorithm>

int* iterative_binary_search( int* first_, int* last_, int search )
{
	auto left = first_;
	auto right = last_ - 1;
	while(*left <= *right)
	{
		auto mid = left + (right - left)/2;
		if(*mid == search)
			return mid;
		if(*mid < search)
			left = mid + 1;
		else
			right = mid - 1;
	}
	return nullptr;	
}

int main( )
{
    int A[] = { 1, 2, 10, 15, 27, 28, 38, 45, 98, 100 };
    int search = 1;

    // Printing the original array.
    std::cout << ">>> Original array  = [ ";
    std::copy( std::begin(A), std::end(A),  std::ostream_iterator<int>( std::cout, " " ) );
    std::cout << "], Size = " <<  std::distance( std::begin(A), std::end(A) ) << "\n";

    // Searching for element
    auto position_element_found = std::distance( std::begin(A), iterative_binary_search( std::begin(A), std::end(A), search ) );

    // Printing the position where the element was found.
    std::cout << ">>> " << search << " found at position -> " << position_element_found << " of the array. " << std::endl << std::endl;
    return EXIT_SUCCESS;
}