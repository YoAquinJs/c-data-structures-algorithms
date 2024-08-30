#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "test-map.h"
#include "utils/utils.h"
#include "searching/test-search.h"
#include "sorting/test-sort.h"

bool PRINT_ON_FAIL = false;

const int CATEGORY_COUNT= 2;
const Category CATEGORIES[] = {
    searching,
    sorting,
};
const char* CATEGORIES_NAMES[] = {
    "searching",
    "sorting",
};
const int TESTS_BY_CATEGORY_COUNT[] = {2, 6};

const int TEST_COUNT = 9;
const Test TESTS[] = {
    // Searching
    __linear_search,
    __binary_search,

    // Sorting
    __bubble_sort,
    __exchange_sort,
    __insertion_sort,
    __selection_sort,
    __merge_sort,
    __quick_sort,

    // Not ran in any group
    __recursive_insertion_sort,
};
const char* TEST_NAMES[] = {
    "linear-search",
    "binary-search",
    "bubble-sort",
    "exchange-sort",
    "insertion-sort",
    "selection-sort",
    "merge-sort",
    "quick-sort",
    "recursive-insertion-sort",
};

Category get_category(const char* category){
    for (int i=0; i < CATEGORY_COUNT; i++){
        if (strcmp(category, CATEGORIES_NAMES[i]) == 0)
            return CATEGORIES[i];
    }
    return invalid;
}

Test get_test(const char* test){
    for (int i=0; i < TEST_COUNT; i++){
        if (strcmp(test, TEST_NAMES[i]) == 0)
            return TESTS[i];
    }
    return invalid;
}

const Test* get_category_tests(Category category){
    return category == 0 ? TESTS : TESTS+TESTS_BY_CATEGORY_COUNT[category-1];
}

bool run_test(Test test){
    printf("running '%s'\n", TEST_NAMES[test]);

    int (*test_to_run)(void) = NULL;
    switch (test) {
    case __linear_search:
        test_to_run = test_linear_search;
        break;
    case __binary_search:
        test_to_run = test_binary_search;
        break;
    case __bubble_sort:
        test_to_run = test_bubble_sort;
        break;
    case __exchange_sort:
        test_to_run = test_exchange_sort;
        break;
    case __insertion_sort:
        test_to_run = test_insertion_sort;
        break;
    case __recursive_insertion_sort:
        test_to_run = test_recursive_insertion_sort;
        break;
    case __selection_sort:
        test_to_run = test_selection_sort;
        break;
    case __merge_sort:
        test_to_run = test_merge_sort;
        break;
    case __quick_sort:
        test_to_run = test_quick_sort;
        break;
    case invalid:
    default:
        break;
    }

    int missing_tests = benchmark_test(test_to_run);
    
    if (missing_tests == 0){
        printf("passed!\n");
        return true;
    }

    printf("missing tests: %d\nfailed!\n", missing_tests);
    return false;
}

void run_all_tests() {
    printf("running all tests...\n");

    for (int i=0; i < TEST_COUNT; i++){
        printf("\n");
        if (!run_test(TESTS[i]))
            exit(EXIT_FAILURE);
    }
}

void run_category_tests(const char *category_name) {
    Category category = get_category(category_name);
    if (category == invalid){
        printf("invalid category\n");
        exit(EXIT_FAILURE);
    }

    printf("running all tests in '%s'...\n", category_name);
    const Test* category_tests = get_category_tests(category);
    for (int i=0; i < TESTS_BY_CATEGORY_COUNT[category]; i++){
        printf("\n");
        if (!run_test(category_tests[i]))
            exit(EXIT_FAILURE);
    }
}

void run_single_test(const char *test_name) {
    Test test = get_test(test_name);
    if (test == invalid){
        printf("invalid test\n");
        exit(EXIT_FAILURE);
    }

    printf("running test...\n\n");
    if (!run_test(test))
        exit(EXIT_FAILURE);
}
