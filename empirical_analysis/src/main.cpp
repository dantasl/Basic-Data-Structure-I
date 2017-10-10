#include "sort_algorithms.h"
#include "build.h"
#include <iostream>
#include <cassert>
#include <chrono>
using namespace std;

bool compare( long a, long b ){ return a < b; }

int main(int const argc, char const **argv)
{
    /* Declaring variables */
    random_device rd;
    mt19937 g(rd());
    vector<unsigned int> A;
    vector<string> sort_names;    
    vector<sort_functions> sort_list;
    unsigned long max_sample_size = 0, i_size;
    bool flag_custom_size = false;
    int i;

    /* Building running environment */
    build_list(argc, argv, sort_list, sort_names);    
    build_sample_size(argc, argv, max_sample_size, flag_custom_size);

    /* First dialog with user */
    cout << endl <<"Running following sort functions: " << endl;
    copy( begin(sort_names), end(sort_names),  ostream_iterator<string>(cout, "   " ) );
    cout << endl << endl <<"With maximum input size: " << max_sample_size << endl << endl;

    /* Filling vector with maximum input and random numbers. TODO: crescent and decrescent */
    build_fill_vector(A, max_sample_size);     

    for(i = 0, i_size = 16; i <= 6; ++i, i_size *= 2) //iterates over each function in vector
    {
        for(unsigned int j = 0; j < sort_list.size(); ++j)
        {
            for(int k = 0; k < 50; ++k)
            {                
                auto end = sort_list[j] == quick_sort ? A.begin() + i_size : A.begin() + i_size - 1;

                auto start_sort = chrono::steady_clock::now();
                sort_list[j]( A, A.begin(), end, compare );
                auto end_sort = chrono::steady_clock::now();
                
                auto time_diff = end_sort - start_sort;
                auto time_real = chrono::duration <double, milli> (time_diff).count();
                
                cout << "Size: " << i_size << " Algoritmo: " << j + 1 << " Execucao: " << k + 1 << " Time: "<< time_real << endl;  
                shuffle(A.begin(), A.begin() + i_size, g); //shuffle so that the vector is unordered again
                cout << "-----------------------------------------" << endl;
            }   
        }    
    }  
}

/*
    25 tamanhos de amostras diferentes
    Cada uma deve ser executada 50 vezes
    50 vezes para cada algoritmo da lista
*/