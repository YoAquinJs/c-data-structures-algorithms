#pragma once
#include <stdbool.h>

#include "../utils/utils.h"

bool is_sorted(int n, int* arr, int* sorted, bool ascendant);

int test_sort(int* (sort)(int, int*), bool inplace, bool ascendant);
