/**
 * @file    sort_algorithms.cpp
 * @brief   Implementing Insertion Sort, Selection Sort, Bubble Sort, Quick Sort, Merge Sort, Shell Sort e Radix Sort.
 * @author  Lucas Gomes Dantas (dantaslucas@ufrn.edu.br)
 * @date    10/10/2017
 */

#include "sort_algorithms.h"

void merge(std::vector<unsigned int> &A, It begin, It middle, It last, Compare cmp)
{
    std::vector<unsigned int> left_array;
    std::vector<unsigned int> right_array;
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

void merge_sort(std::vector<unsigned int> &A, It begin, It end, Compare cmp)
{
    if(begin < end)
    {
        auto middle = begin + (end - begin)/2;
        merge_sort(A, begin, middle, cmp);
        merge_sort(A, middle + 1, end, cmp);
        merge(A, begin, middle, end, cmp);
    }    
}

void insertion_sort(std::vector<unsigned int> &A, It begin, It last, Compare cmp )
{
    auto it = begin;
    for(; it != last + 1; ++it)
    {
        auto carry = it;
        while( carry != begin and cmp(*carry, *(carry - 1)) )
        {
            std::swap( *carry, *(carry-1) );
            carry--;
        }
    }  
}

void bubble_sort(std::vector<unsigned int> &A, It begin, It last, Compare cmp )
{
    auto it = begin;
    while(true)
    {
        bool continue_bubble = false;
        for(it = begin; it != last; ++it)
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

It partition(It begin, It last, Compare cmp)
{
    auto pivot = last - 1;
    auto fast = begin;
    auto slow = begin;
    for(; fast != last; ++fast)
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

void quick_sort(std::vector<unsigned int> &A, It begin, It last, Compare cmp )
{
   if(begin < last)
   {
        auto partitioned = partition(begin, last, cmp);
        quick_sort(A, begin, partitioned, cmp);
        quick_sort(A, partitioned + 1, last, cmp);        
   }     
}

void selection_sort(std::vector<unsigned int> &A, It begin, It last, Compare cmp )
{
    auto it = begin;
    auto j = begin;
    for(; it != last + 1; ++it)
    {
        auto current_minimum = it;
        for(j = it; j != last + 1; ++j)
        {
            if( cmp( *j, *current_minimum ) )
                current_minimum = j; 
        }
        std::swap(*it, *current_minimum);    
    }  
}

void shell_sort(std::vector<unsigned int> &A, It begin, It end, Compare cmp)
{
    unsigned long distance = std::distance(begin, end + 1);
    for (auto gap = distance/2; gap > 0; gap /= 2)
    {
        for (auto i = gap; i < distance; i += 1)
        {
            auto temp = A[i];
            unsigned long j;            
            for (j = i; j >= gap && cmp(temp, A[j - gap]); j -= gap)
                A[j] = A[j - gap];
            A[j] = temp;
        }
    }   
}

long int get_max_value(It begin, It end, Compare cmp)
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

void radix_sort(std::vector<unsigned int> &A, It begin, It end, Compare cmp)
{
    long int max_input = get_max_value(begin, end + 1, cmp);
    auto len_a = std::distance(begin, end + 1);     
    for (auto radix = 1; max_input/radix > 0; radix *= 10)
    {
        int buckets[10] = { 0 };
        std::vector<unsigned int> aux;
        aux.resize(len_a);  
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