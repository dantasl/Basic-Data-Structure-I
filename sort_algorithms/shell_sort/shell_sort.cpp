//    Compile: g++ -Wall -std=c++11 shell_sort.cpp -o shell_sort

#include <iostream> // cout, endl
#include <iterator> // distance
#include <algorithm> // copy, swap
#include <vector>

bool compare( int a, int b ){ return ( a < b ); }

template< typename T, typename P, typename Compare >
void shell_sort(std::vector<T> &A, P begin, P end, Compare cmp)
{
	auto gap = A.size()/2;
	while(gap > 0)
	{
		for(auto i = 0; i < A.size() - gap; ++i)
		{
			auto temp = A[i];
			auto j = i;
			while( j >= gap and cmp( temp, A[j - gap] ) ) // insertion sort part
	        {
	            std::swap(A[j], A[j - gap]);
	            j-=gap;
	        }
		}
		gap /= 2;	
	}	
}

int main()
{
    std::vector<int> A = { 61, 109, 149, 111, 34, 2, 24, 119, 122, 125, 27, 145 };
    //std::vector<int> A = { 1, 2, 3, 4, 5, 6, 7 };

    std::cout << ">>> Original array: ";
    std::copy( std::begin(A), std::end(A),  std::ostream_iterator<int>( std::cout, " " ) );
    std::cout << std::endl;

    shell_sort( A, std::begin(A), std::end(A) - 1, compare );
    
    std::cout << ">>> Sorted array: ";
    std::copy( std::begin(A), std::end(A),  std::ostream_iterator<int>( std::cout, " " ) );
    std::cout << std::endl;

    return 0;
}