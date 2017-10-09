#include "sort_algorithms.h"
#include "build.h"
#include <iostream>
#include <cassert>
using namespace std;

bool compare( long a, long b ){ return a < b; }

int main(int const argc, char const **argv)
{
    /* Declaring variables */
    vector<unsigned int> A;
    vector<string> sort_names;    
    vector<sort_functions> sort_list;
    unsigned long max_sample_size = 0;
    bool flag_custom_size = false;

    /* Building running environment */
    build_list(argc, argv, sort_list, sort_names);    
    build_sample_size(argc, argv, max_sample_size, flag_custom_size);

    /* First dialog with user */
    cout << endl <<"Running following sort functions: " << endl;
    std::copy( std::begin(sort_names), std::end(sort_names),  std::ostream_iterator<string>( std::cout, "   " ) );
    cout << endl << endl <<"With maximum input size: " << max_sample_size << endl << endl;

    /* Filling vector with maximum input and random numbers. TODO: crescent and decrescent */
    build_fill_vector(A, max_sample_size);       

    /*random_device rd;
    mt19937 g(rd());

    //filling vector
    A.resize(1000);
    iota(A.begin(), A.end(), 1);
    shuffle(A.begin(), A.end(), g);

    //vector<int> max_size;
    //max_size.resize(1073741824); //2³⁰

    for(unsigned int i = 0; i < sort_list.size(); ++i) //iterates over each function in vector
    {
        auto end = sort_list[i] == quick_sort ? A.end() : A.end() - 1;
        sort_list[i]( A, A.begin(), end, compare );
        for(unsigned int j = 0; j < A.size(); ++j) //checks if the ordenation is successfull
            assert( (j + 1) == A[j] );        
        shuffle(A.begin(), A.end(), g); //shuffle so that the vector is unordered again
        cout << "-----------------------------------------" << endl;
    } */
    
}