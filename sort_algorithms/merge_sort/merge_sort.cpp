//    Compile: g++ -Wall -std=c++11 merge_sort.cpp -o merge_sort

#include <iostream> // cout, endl
#include <iterator> // distance
#include <algorithm> // copy, swap
#include <vector>

bool compare( int a, int b ){ return ( a < b ); }

template< typename T, typename P, typename Compare >
void merge(std::vector<T> &A, P begin, P middle, P last, Compare cmp)
{
    std::vector<T> left_array;
    std::vector<T> right_array;

    for (auto i = begin; i <= middle; ++i)
        left_array.push_back(*i);
    for (auto j = middle + 1; j <= last; ++j)
        right_array.push_back(*j);

    auto i = left_array.begin();
    auto j = right_array.begin();
    auto to_merge = begin;

    while(i != left_array.end() and j != right_array.end())
    {
        if( cmp(*i, *j) )
            std::swap(*to_merge++, *i++);
        else
            std::swap(*to_merge++, *j++); 
    }

    if(i < left_array.end())
    {
        for(; i != left_array.end(); ++i)
            std::swap(*to_merge++, *i);
    }
    else
    {
        for(; j != right_array.end(); ++j)
            std::swap(*to_merge++, *j);
    }
}

template< typename T, typename P, typename Compare >
void merge_sort(std::vector<T> &A, P begin, P end, Compare cmp)
{
    if(begin < end)
    {
        auto middle = begin + (end - begin)/2;
        merge_sort(A, begin, middle, cmp);
        merge_sort(A, middle + 1, end, cmp);
        merge(A, begin, middle, end, cmp);
    }   
    
}

int main()
{
    std::vector<int> A = { 12, 1, 3, 2, 7, 90, 45, 11, 45 };
    //std::vector<int> A = { 1, 2, 3, 4, 5, 6, 7 };

    std::cout << ">>> Original array: ";
    std::copy( std::begin(A), std::end(A),  std::ostream_iterator<int>( std::cout, " " ) );
    std::cout << std::endl;

    merge_sort( A, std::begin(A), std::end(A) - 1, compare );

    std::cout << ">>> Sorted array: ";
    std::copy( std::begin(A), std::end(A),  std::ostream_iterator<int>( std::cout, " " ) );
    std::cout << std::endl;

    return 0;
}