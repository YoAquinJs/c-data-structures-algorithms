#pragma once
#include <stdbool.h>

typedef void (Sort)(int, int*);
int test_sort(Sort sort, bool ascendant);

int test_selection_sort();
int test_insertion_sort();
int test_recursive_insertion_sort();
int test_exchange_sort();
int test_bubble_sort();
int test_merge_sort();
int test_quick_sort();
