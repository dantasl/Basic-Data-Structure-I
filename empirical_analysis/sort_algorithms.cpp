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

template< typename FwrdIt, typename Compare >
void insertion_sort(FwrdIt _begin, FwrdIt _last, Compare cmp )
{
    auto it = _begin;
    for(; it != _last; ++it)
    {
        auto carry = it;
        while( carry != _begin and cmp(*carry, *(carry - 1)) )
        {
            std::swap( *carry, *(carry-1) );
            carry--;
        }
    }  
}

template< typename FwrdIt, typename Compare >
void bubble_sort(FwrdIt _begin, FwrdIt _last, Compare cmp )
{
    auto it = _begin;
    while(true)
    {
        bool continue_bubble = false;
        for(it = _begin; it != _last - 1; ++it)
        {
            if( cmp( *(it + 1), *it ) )
            {
                std::swap( *(it + 1), *it );
                continue_bubble = true;
            }
        }
        if(!continue_bubble)
            break;   
    }    
}

template< typename FwrdIt, typename Compare >
FwrdIt partition(FwrdIt _begin, FwrdIt _last, Compare cmp)
{
    auto pivot = _last - 1;
    auto fast = _begin;
    auto slow = _begin;
    for(; fast != _last; ++fast)
    {
        if( cmp(*fast, *pivot) )
        {
            std::swap( *slow, *fast );
            slow++;
        }   
    }
    std::swap(*slow, *pivot);
    return slow;
}

template< typename FwrdIt, typename Compare >
void quick_sort(FwrdIt _begin, FwrdIt _last, Compare cmp )
{
   if(_begin < _last)
   {
        auto partitioned = partition(_begin, _last, cmp);
        quick_sort(_begin, partitioned, cmp);
        quick_sort(partitioned + 1, _last, cmp);        
   }     
}

template< typename FwrdIt, typename Compare >
void selection_sort(FwrdIt _begin, FwrdIt _last, Compare cmp )
{
    auto it = _begin; // points to the beginning of the range
    auto j = _begin;
    for(; it != _last; ++it) //iterates over each member to sort
    {
        auto current_minimum = it;
        for(j = it; j != _last; ++j)
        {
            if( cmp( *j, *current_minimum ) )
                current_minimum = j; 
        }
        std::swap(*it, *current_minimum);    
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