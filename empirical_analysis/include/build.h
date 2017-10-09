#ifndef _BUILD_H_
#define _BUILD_H_

#include "sort_algorithms.h"
#include <cstring>
#include <stdlib.h>
using namespace std;

void build_list(int const argc, char const **argv, vector<sort_functions> &sort_list, vector<string> &names);

void build_sample_size(int const argc, char const **argv, unsigned long &sample_max_size, bool &custom_size);

#endif