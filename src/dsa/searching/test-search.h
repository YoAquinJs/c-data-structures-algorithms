#pragma once
#include <stdbool.h>

typedef int(Search)(int, int*, int);
int TestSearch(Search search);

int TestLinearSearch();
int TestBinarySearch();
