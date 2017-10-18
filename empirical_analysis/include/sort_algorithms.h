/**
 * @file    sort_algorithms.h
 * @brief   Defining prototypes for the sort functions used in the analysis.
 *			Since all these functions were implemented at class and they're well known and spread across
 * 			the community, no further documentation will be added here. 
 * @author  Lucas Gomes Dantas (dantaslucas@ufrn.edu.br)
 * @date    10/10/2017
 */

#ifndef _SORT_ALGORITHMS_H_
#define _SORT_ALGORITHMS_H_

#include <iterator>
#include <algorithm>
#include <vector>
#include <random>
#include <string>

typedef bool (*Compare)(long, long);
using It = std::vector<unsigned int>::iterator; //creating an alias
typedef void (*sort_functions) (std::vector<unsigned int> &, It, It, Compare);

void merge(std::vector<unsigned int> &A, It begin, It middle, It last, Compare cmp);

void merge_sort(std::vector<unsigned int> &A, It begin, It end, Compare cmp);

void insertion_sort(std::vector<unsigned int> &A, It begin, It last, Compare cmp);

void bubble_sort(std::vector<unsigned int> &A, It begin, It last, Compare cmp);

It partition(It begin, It last, Compare cmp);

void quick_sort(std::vector<unsigned int> &A, It begin, It last, Compare cmp);

void selection_sort(std::vector<unsigned int> &A, It begin, It last, Compare cmp);

void shell_sort(std::vector<unsigned int> &A, It begin, It end, Compare cmp);

long int get_max_value(It begin, It end, Compare cmp);

void radix_sort(std::vector<unsigned int> &A, It begin, It end, Compare cmp);

#endif