#pragma once
#include <stdbool.h>

typedef int (Search)(int, int*, int);
int test_search(Search search);

int linear_search(int n, int* arr, int elem);
int binary_search(int n, int* arr, int key);
