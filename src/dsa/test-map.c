#include "test-map.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../utils/utils.h"
#include "searching/test-search.h"
#include "sorting/test-sort.h"

bool PRINT_ON_FAIL = false;

const int CATEGORY_COUNT = 2;
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
    __linear_search, __binary_search,

    // Sorting
    __bubble_sort, __exchange_sort, __insertion_sort, __selection_sort,
    __merge_sort, __quick_sort,

    // Not ran in any group
};
const char* TEST_NAMES[] = {
    "linear-search",  "binary-search",  "bubble-sort", "exchange-sort",
    "insertion-sort", "selection-sort", "merge-sort",  "quick-sort",
};

Category GetCategory(const char* category) {
    for (int i = 0; i < CATEGORY_COUNT; i++) {
        if (strcmp(category, CATEGORIES_NAMES[i]) == 0) return CATEGORIES[i];
    }
    return invalid;
}

Test GetTest(const char* test) {
    for (int i = 0; i < TEST_COUNT; i++) {
        if (strcmp(test, TEST_NAMES[i]) == 0) return TESTS[i];
    }
    return invalid;
}

const Test* get_category_tests(Category category) {
    return category == 0 ? TESTS
                         : TESTS + TESTS_BY_CATEGORY_COUNT[category - 1];
}

bool RunTest(Test test) {
    printf("running '%s'\n", TEST_NAMES[test]);

    int (*test_to_run)(void) = NULL;
    switch (test) {
        case __linear_search:
            test_to_run = TestLinearSearch;
            break;
        case __binary_search:
            test_to_run = TestBinarySearch;
            break;
        case __bubble_sort:
            test_to_run = TestBubbleSort;
            break;
        case __exchange_sort:
            test_to_run = TestExchangeSort;
            break;
        case __insertion_sort:
            test_to_run = TestInsertionSort;
            break;
        case __selection_sort:
            test_to_run = TestSelectionSort;
            break;
        case __merge_sort:
            test_to_run = TestMergeSort;
            break;
        case __quick_sort:
            test_to_run = TestQuickSort;
            break;
        case invalid:
        default:
            break;
    }

    int missing_tests = BenchmarkTest(test_to_run);

    if (missing_tests == 0) {
        printf("passed!\n");
        return true;
    }

    printf("missing tests: %d\nfailed!\n", missing_tests);
    return false;
}

void RunAllTests() {
    printf("running all tests...\n");

    for (int i = 0; i < TEST_COUNT; i++) {
        printf("\n");
        if (!RunTest(TESTS[i])) exit(EXIT_FAILURE);
    }
}

void RunCategoryTests(const char* category_name) {
    Category category = GetCategory(category_name);
    if (category == invalid) {
        printf("invalid category\n");
        exit(EXIT_FAILURE);
    }

    printf("running all tests in '%s'...\n", category_name);
    const Test* category_tests = get_category_tests(category);
    for (int i = 0; i < TESTS_BY_CATEGORY_COUNT[category]; i++) {
        printf("\n");
        if (!RunTest(category_tests[i])) exit(EXIT_FAILURE);
    }
}

void RunSingleTest(const char* test_name) {
    Test test = GetTest(test_name);
    if (test == invalid) {
        printf("invalid test\n");
        exit(EXIT_FAILURE);
    }

    printf("running test...\n\n");
    if (!RunTest(test)) exit(EXIT_FAILURE);
}
