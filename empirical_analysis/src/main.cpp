#include "sort_algorithms.h"
#include "build.h"
#include <iostream>
#include <chrono>
#include <fstream>
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
    ofstream sort_times;
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

    sort_times.open("time/sort_times.csv", ios_base::trunc);
    sort_times << "Algorithm, Input Size, Average Time" << endl; //writing header

    for(i = 0, i_size = 16; i < 25; ++i, i_size *= 2) //iterates over each function in vector
    //for(i = 0, i_size = 1; i <= 10; ++i, i_size *= 2)
    {
        for(unsigned int j = 0; j < sort_list.size(); ++j)
        {
            for(int k = 1; k <= 50; ++k)
            {                
                auto end = sort_list[j] == quick_sort ? A.begin() + i_size : A.begin() + i_size - 1;
                
                // Calculates running time for each sorting algorithm
                // ========================================================================================
                auto start_sort = chrono::steady_clock::now();
                sort_list[j]( A, A.begin(), end, compare );
                auto end_sort = chrono::steady_clock::now();
                // ========================================================================================

                // Calculates moving average for the 50 executions
                // ========================================================================================
                auto time_diff = end_sort - start_sort;
                double time_average = 0.00;
                time_average = ( chrono::duration <double, milli> (time_diff).count() - time_average )/k + time_average;
                // ========================================================================================

                cout << "Size: " << i_size << " Algorithm: " << j + 1 << " Execution: " << k << " Time: "<< time_average << endl;
                cout << "------------------------------------------------------" << endl;

                // When the code reaches the 50th execution, the average can be stored in a file
                // ========================================================================================
                if(k == 50)
                    sort_times << sort_names[j] << ", " << i_size << ", " << time_average << endl;
                // ========================================================================================       
            }   
        }    
    }
    build_plot_graph();
}