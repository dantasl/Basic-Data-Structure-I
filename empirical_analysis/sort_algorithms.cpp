bool compare( auto a, auto b ){ return ( a < b ); }

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
    auto it = _begin;
    auto j = _begin;
    for(; it != _last; ++it)
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
            while( j >= gap and cmp( temp, A[j - gap] ) )
            {
                std::swap(A[j], A[j - gap]);
                j-=gap;
            }
        }
        gap /= 2;   
    }   
}

template< typename P, typename Compare >
int get_max_value(P begin, P end, Compare cmp)
{
    auto slow = begin;
    auto fast = begin;
    for(; fast != end; ++fast)
    {
        if( cmp( *slow, *fast ) )   
            slow = fast;
    }
    return *slow;   
}

template< typename T, typename P, typename Compare >
void radix_sort(std::vector<T> &A, P begin, P end, Compare cmp)
{
    auto max_input = get_max_value(A.begin(), A.end(), cmp);
    auto len_a = std::distance(A.begin(), A.end());     
    for (auto radix = 1; max_input/radix > 0; radix *= 10)
    {
        int buckets[10] = { 0 };
        int aux[len_a];  
        for (auto i = 0; i < len_a; ++i)
            buckets[ (A[i] / radix) % 10 ]++;    
        for (auto i = 1; i < 10; ++i)
            buckets[i] += buckets[i - 1];    
        for (auto i = len_a - 1; i >= 0; --i)
        {
            aux[ buckets[ ( A[i] / radix ) % 10 ] - 1 ] = A[i];
            buckets[ (A[i]/radix)%10 ]--;
        }
        for (auto i = 0; i < len_a; ++i)
            A[i] = aux[i];        
    }    
}

int main()
{
    std::vector<int> A = { 61, 109, 149, 111, 34, 2, 24, 119, 122, 125, 27, 145 };
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

/** TODO: deixar todo mundo com a mesma assinatura e funcionando ao chamado da main.*/