#include <iostream>
#include <iterator>

//g++ -Wall -std=c++11 filter_students.cpp -o filter_students
// TODO : Makefile, Explain Logic Later

int *filter( int *first_, int *last_ )
{
    auto slow = first_;
    auto fast = first_;
    while ( fast != last_ )
    {
        if( *fast > 0 )
        {
            *slow = *fast;
            slow++;
        }
        fast++;    
    }    
    return slow;
}

int main( )
{
    int A[] = { -2, -8, 6, 7, -3, 10, 1, 0, -3, 7 };

    // Printing the filtered array.
    std::cout << ">>> Original array  = [ ";
    std::copy( std::begin(A), std::end(A),  std::ostream_iterator<int>( std::cout, " " ) );
    std::cout << "], Size = " <<  std::distance( std::begin(A), std::end(A) ) << "\n";

    // Filtering
    auto new_end = filter( std::begin(A), std::end(A) );

    // Printing the filtered array.
    std::cout << ">>> FILTERED array  = [ ";
    std::copy( std::begin(A), new_end,  std::ostream_iterator<int>( std::cout, " " ) );
    std::cout << "], Size = " <<  std::distance( std::begin(A), new_end ) << "\n";

    return EXIT_SUCCESS;
}