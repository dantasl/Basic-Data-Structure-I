//    Compile: g++ -Wall -std=c++11 radix_sort.cpp -o radix_sort

#include <iostream> // cout, endl
#include <iterator> // distance
#include <algorithm> // copy, swap
#include <vector>

bool compare( int a, int b ){ return ( a < b ); }

template< typename P, typename Compare >
int get_max_value(P begin, P end, Compare cmp)
{
	auto slow = begin;
	auto fast = begin;
	for(; fast != end; ++fast)
	{
		if( cmp( *slow, *fast ) )	
			slow = fast;
	}
	return *slow;	
}

template< typename T, typename P, typename Compare >
void radix_sort(std::vector<T> &A, P begin, P end, Compare cmp)
{
    auto max_input = get_max_value(A.begin(), A.end(), cmp);
    auto len_a = std::distance(A.begin(), A.end());     
    for (auto radix = 1; max_input/radix > 0; radix *= 10)
    {
    	int buckets[10] = { 0 };
		int aux[len_a];	 
	    for (auto i = 0; i < len_a; ++i)
	        buckets[ (A[i] / radix) % 10 ]++;	 
	    for (auto i = 1; i < 10; ++i)
	        buckets[i] += buckets[i - 1];	 
	    for (auto i = len_a - 1; i >= 0; --i)
	    {
	        aux[ buckets[ ( A[i] / radix ) % 10 ] - 1 ] = A[i];
	        buckets[ (A[i]/radix)%10 ]--;
	    }
	    for (auto i = 0; i < len_a; ++i)
            A[i] = aux[i];        
    }    
}

int main()
{
    std::vector<int> A = { 12, 1, 3, 2, 7, 90, 45, 11, 45 };
    //std::vector<int> A = { 1, 2, 3, 4, 5, 6, 7 };

    std::cout << ">>> Original array: ";
    std::copy( std::begin(A), std::end(A),  std::ostream_iterator<int>( std::cout, " " ) );
    std::cout << std::endl;

    radix_sort( A, std::begin(A), std::end(A) - 1, compare );
    
    std::cout << ">>> Sorted array: ";
    std::copy( std::begin(A), std::end(A),  std::ostream_iterator<int>( std::cout, " " ) );
    std::cout << std::endl;

    return 0;
}