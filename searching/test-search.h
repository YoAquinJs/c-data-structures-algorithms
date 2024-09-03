#pragma once
#include <stdbool.h>

typedef int (Search)(int, int*, int);
int test_search(Search search);

int test_linear_search();
int test_binary_search();
