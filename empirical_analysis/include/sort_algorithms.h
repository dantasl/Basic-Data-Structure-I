#ifndef _SORT_ALGORITHMS_H_
#define _SORT_ALGORITHMS_H_

#include <iterator> // distance
#include <algorithm> // copy, swap
#include <vector>
#include <random>

typedef bool (*Compare)(long, long);
using It = std::vector<unsigned int>::iterator; //creating an alias
typedef void (*sort_functions) (std::vector<unsigned int> &, It, It, Compare);

void merge(std::vector<unsigned int> &A, It begin, It middle, It last, Compare cmp);

void merge_sort(std::vector<unsigned int> &A, It begin, It end, Compare cmp);

void insertion_sort(std::vector<unsigned int> &A, It begin, It last, Compare cmp );

void bubble_sort(std::vector<unsigned int> &A, It begin, It last, Compare cmp );

It partition(It begin, It last, Compare cmp);

void quick_sort(std::vector<unsigned int> &A, It begin, It last, Compare cmp );

void selection_sort(std::vector<unsigned int> &A, It begin, It last, Compare cmp );

void shell_sort(std::vector<unsigned int> &A, It begin, It end, Compare cmp);

long int get_max_value(It begin, It end, Compare cmp);

void radix_sort(std::vector<unsigned int> &A, It begin, It end, Compare cmp);

#endif