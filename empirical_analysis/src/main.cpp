#include "sort_algorithms.h"
#include <iostream>
#include <cassert>
using namespace std;

bool compare( long a, long b ){ return a < b; }

int main()
{
    random_device rd;
    mt19937 g(rd());

    //filling vector
    vector<unsigned int> A;
    A.resize(1000);
    iota(A.begin(), A.end(), 1);
    shuffle(A.begin(), A.end(), g);

    //vector<int> max_size;
    //max_size.resize(1073741824); //2³⁰

    vector<sort_functions> sort_list = { 
        insertion_sort, selection_sort, bubble_sort,
        quick_sort, merge_sort, shell_sort, radix_sort
    };

    for(unsigned int i = 0; i < sort_list.size(); ++i) //iterates over each function in vector
    {
        auto end = sort_list[i] == quick_sort ? A.end() : A.end() - 1;
        sort_list[i]( A, A.begin(), end, compare );
        for(unsigned int j = 0; j < A.size(); ++j) //checks if the ordenation is successfull
            assert( (j + 1) == A[j] );        
        shuffle(A.begin(), A.end(), g); //shuffle so that the vector is unordered again
        cout << "-----------------------------------------" << endl;
    }
}