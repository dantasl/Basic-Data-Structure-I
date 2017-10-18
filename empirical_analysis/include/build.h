/**
 * @file    build.h
 * @brief   Creating prototypes for auxiliary functions that will help running the empirical analysis.
 * @author  Lucas Gomes Dantas (dantaslucas@ufrn.edu.br)
 * @date    10/10/2017
 */

#ifndef _BUILD_H_
#define _BUILD_H_

#include "sort_algorithms.h"
#include <cstring>
#include <stdlib.h>
using namespace std;

/**
 * This function verifies if the user passed -f as param. If so, consumes the whole array of params
 * searching (case sensitive) for the names typed. Every time a name of a valid function is typed
 * the program adds it to the vector of functions. If user types names of inexistent functions, no error occurrs.
 * The exact order that the user typed the names is the order that their respective functions will be executed.
 * If the user does not type -f, default functions are used.
 * \param argc Number of params provided by the user.
 * \param argv Params written by the user.
 * \sort_list A vector in which pointers to functions are going to be stored.
 * \names A vector containing the names of the functions that will be executed.
 */

void build_list(int const argc, char const **argv, vector<sort_functions> &sort_list, vector<string> &names);

/**
 *	This function gets the immediate value after -ri and sets it as the maximum sample size.
 *	Note: using this argument the program will only execute for this value, no more than it.
 *	If the user only types -ri and nothing after it, program takes 0 as maximum value.
 *	If the user types -ri followed by only chars, program takes 0 as maximum value.
 *  If user does not type -ri, default max size for the samples is used.
 *	Since we need to tell the program to execute only for this maximum sample size, there is a need
 *	for a flag.
 *  \param argc Number of params provided by user.
 *  \param argv Params written by the user.
 *  \param sample_max_size Variable to store the max size of the samples
 *  \param custom_size Bool that will act as flag. At the end of the function, if its value is true,
 *  	   the user provided a custom max size. If not, the code should run with default configurations for the max size.
 */
void build_sample_size(int const argc, char const **argv, unsigned long &sample_max_size, bool &custom_size);

/**
 * This function receives a vector and fills it with increasing numbers until it reaches the maximum input size
 * provided by the user.
 * \param A Vector that will be populated.
 * \param sample_max_size Maximum size for the vector.	
 */
void build_fill_vector(vector<unsigned int> &A, unsigned long const &sample_max_size);

#endif