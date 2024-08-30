#pragma once
#include <stdbool.h>

typedef void (Sort)(int, int*);
int test_sort(Sort sort, bool ascendant);

void test_selection_sort();
void test_insertion_sort();
void test_recursive_insertion_sort();
void test_exchange_sort();
void test_bubble_sort();
void test_merge_sort();
void test_quick_sort();
