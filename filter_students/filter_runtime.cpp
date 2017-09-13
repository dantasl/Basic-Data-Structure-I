#include <iostream>
#include <fstream>
#include <sstream>
#include <random>
#include <vector>
#include <chrono>
#include <iterator>

#define N 20 // Number of 

//Fill a vector with random numbers in the range [lower, upper]
void randomFill( std::vector<int> &V, const int lower, const int upper, const unsigned int seed)
{
    //use the default random engine and an uniform distribution
    std::default_random_engine eng(seed);
    std::uniform_real_distribution<double> distr(lower, upper);

    // Fill up vector
    for( auto &elem : V)
        elem = distr(eng);
}

template < typename T >
T filter_1( T first_, T last_ )
{
    auto slow(first_);
    auto fast(first_);
    while( fast != last_ )
    {
        if( *fast > 0 )
            *slow++ = *fast;
        fast++;
    }
    return slow;
}

template < typename T >
T filter_2( T first_, T last_ )
{
    while( first_ != last_ )
    {
        // Whenever we got a negative number we shift the remaining elements
        // one position to the left, overwriting the excluded number.
#ifdef DEBUG
        std::cout << ">>> Looking at " << *first_ << '\n';
#endif
        if ( *first_ <= 0 )
        {
#ifdef DEBUG
            std::cout << ">>> Elimination process started.\n";
#endif
            auto work( first_ );
            while ( work != std::prev(last_) )
            {
#ifdef DEBUG
                std::cout << "\t>> Copying " << *(work+1) << " over " << *work << ".\n";
#endif
                *work = *(work+1);
                work++;
            }
            last_--;
#ifdef DEBUG
            std::cout << ">>> New array: [ ";
            std::copy( first_, last_, std::ostream_iterator<int>( std::cout, " " ) );
            std::cout << "]\n";
#endif
        }
        else
        {
#ifdef DEBUG
            std::cout << ">>> Accept element.\n";
#endif
            first_++; // Advance processing towards the array's end.
        }
    }
    return first_;
}

int main( int argc, char * argv[] )
{
    auto arrSz( 0ul );

    if ( argc > 1 )
    {
        std::stringstream( argv[1] ) >> arrSz;
    }
    else
    {
        arrSz = N;
    }

    std::cout << ">>> Required array size is: " << arrSz << std::endl;

    // Store the data.
    std::vector< int > V( arrSz );

    // Seed with a real random value, if available.
    std::random_device r;
    // Fill it up with random integers.
    randomFill( V, -100, 100, r() );
    //randomFill( V, -100, 0, r() ); // worst
    //randomFill( V, 1, 100, r() );  // best

#ifdef PRINT
    // Printing out the array, just to make sure we've got random integers.
    std::cout << ">>> ORIGINAL Vet = [ ";
    std::copy( V.begin(), V.end(), std::ostream_iterator<int>( std::cout, " " ) );
    std::cout << "], Size = " << arrSz << "\n";
#endif


    std::cout << ">>> STARTING computation that needs timing <<<\n";
    auto start = std::chrono::steady_clock::now();
    //================================================================================
#ifdef QUAD
    std::cout << ">>> QUADRATIC...\n";
    auto new_end = filter_2( V.begin(), V.end() );
#else
    std::cout << ">>> LINEAR...\n";
    auto new_end = filter_1( V.begin(), V.end() );
#endif

    //================================================================================
    auto end = std::chrono::steady_clock::now();
    std::cout << ">>> ENDING computation that needs timing <<<\n";
 
    //Store the time difference between start and end
    auto diff = end - start;

    // Milliseconds (10^-3)
    std::cout << "\t\t>>> " << std::chrono::duration <double, std::milli> (diff).count() << " ms" << std::endl;

    // Nanoseconds (10^-9)
    std::cout << "\t\t>>> " << std::chrono::duration <double, std::nano> (diff).count() << " ns" << std::endl;

    // Seconds
    auto diff_sec = std::chrono::duration_cast<std::chrono::seconds>(diff);
    std::cout << "\t\t>>> " << diff_sec.count() << " s" << std::endl;

#ifdef PRINT
    // Printing compacted array.
    std::cout << ">>> Vet COMPACTED = [ ";
    std::copy( V.begin(), new_end, std::ostream_iterator<int>( std::cout, " " ) );
    std::cout << "], Size = " <<  std::distance( V.begin(), new_end ) << "\n";
#endif


    return EXIT_SUCCESS;

}



