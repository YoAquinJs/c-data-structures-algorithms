#pragma once

#include <stdbool.h>

extern bool PRINT_ON_FAIL;

#define invalid -1

typedef enum{
    invalid_c=-1,
    searching,
    sorting,
} Category;
extern const int CATEGORY_COUNT;
extern const Category CATEGORIES[];
extern const char* CATEGORIES_NAMES[];

typedef enum{
    invalid_t=-1,
    __linear_search,
    __binary_search,
    __bubble_sort,
    __exchange_sort,
    __insertion_sort,
    __selection_sort,
    __merge_sort,
    __quick_sort,
} Test;
extern const int TEST_COUNT;
extern const Test TESTS[];
extern const char* TEST_NAMES[];

extern const int TESTS_BY_CATEGORY_COUNT[];
extern const Test* TESTS_BY_CATEGORY[];

Category get_category(const char* category);
Test get_test(const char* test);

const Test* get_category_tests(Category category);
bool run_test(Test test);

void run_all_tests();
void run_category_tests(const char *category);
void run_single_test(const char *test_name);
