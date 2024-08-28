#pragma once

#include <stdbool.h>

bool print_on_fail = false;

#define invalid -1

typedef enum{
    invalid_c=-1,
    searching,
    sorting,
} Category;

typedef enum{
    invalid_t=-1,
    _linear_search,
    _binary_search,
    _bubble_sort,
    _exchange_sort,
    _insertion_sort,
    _selection_sort,
    _merge_sort,
} Test;

Category get_category(char* category);
Test get_test(char* test);

void run_category(Category category);
void run_test(Test test);
