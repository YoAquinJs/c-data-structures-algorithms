#pragma once
#include <stdbool.h>

typedef int (Search)(int, int*, int);
int test_search(Search search);

void test_linear_search();
void test_binary_search();
