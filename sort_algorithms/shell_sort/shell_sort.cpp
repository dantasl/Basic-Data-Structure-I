//    Compile: g++ -Wall -std=c++11 shell_sort.cpp -o shell_sort

#include <iostream> // cout, endl
#include <iterator> // distance
#include <algorithm> // copy, swap
#include <vector>
using namespace std;

bool compare( int a, int b ){ return ( a < b ); }

template< typename T, typename P, typename Compare >
void shell_sort(std::vector<T> &A, P begin, P end, Compare cmp)
{
    for (auto gap = A.size()/2; gap > 0; gap /= 2)
    {
        for (auto i = gap; i < A.size(); i += 1)
        {
            auto temp = A[i];
            long j;            
            for (j = i; j >= gap && cmp(temp, A[j - gap]); j -= gap)
                A[j] = A[j - gap];
            A[j] = temp;
        }
    }
}

int main()
{
	random_device rd;
    mt19937 g(rd());
	vector<int> A;
    A.resize(50);
    iota(A.begin(), A.end(), 1);
    shuffle(A.begin(), A.end(), g);

    std::cout << ">>> Original array: ";
    std::copy( std::begin(A), std::end(A),  std::ostream_iterator<int>( std::cout, " " ) );
    std::cout << std::endl;

    shell_sort( A, std::begin(A), std::end(A), compare );
    
    std::cout << ">>> Sorted array: ";
    std::copy( std::begin(A), std::end(A),  std::ostream_iterator<int>( std::cout, " " ) );
    std::cout << std::endl;

    return 0;
}