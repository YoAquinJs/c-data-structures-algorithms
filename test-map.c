#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "test-map.h"
#include "searching/test-search.h"
#include "sorting/test-sort.h"

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

const int TEST_COUNT = 8;
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

    int missing_tests;
    switch (test) {
    case __linear_search:
        missing_tests = test_search(linear_search);
        break;
    case __binary_search:
        missing_tests = test_search(binary_search);
        break;
    case __bubble_sort:
        missing_tests = test_sort(bubble_sort, true);
        break;
    case __exchange_sort:
        missing_tests = test_sort(exchange_sort, true);
        break;
    case __insertion_sort:
        missing_tests = test_sort(insertion_sort, true);
        break;
    case __selection_sort:
        missing_tests = test_sort(selection_sort, true);
        break;
    case __merge_sort:
        missing_tests = test_sort(merge_sort, true);
        break;
    case __quick_sort:
        missing_tests = test_sort(quick_sort, true);
        break;
    case invalid:
    default:
        break;
    }
    
    if (missing_tests == 0)
        printf("passed!\n");
    else
        printf("missing tests: %d\nfailed!\n", missing_tests);

    return missing_tests;
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
    Test* category_tests = get_category_tests(category);
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
