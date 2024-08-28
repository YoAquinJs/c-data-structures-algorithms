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

Test* get_category_tests(Category category){
    return category == 0 ? TESTS : TESTS+TESTS_BY_CATEGORY_COUNT[category-1];
}

bool run_test(Test test){
    printf("running '%s'\n", TEST_NAMES[test]);

    bool passed;
    switch (test) {
    case __linear_search:
        passed = 0 == test_search(linear_search);
        break;
    case __binary_search:
        passed = 0 == test_search(binary_search);
        break;
    case __bubble_sort:
        passed = 0 == test_sort(bubble_sort, true);
        break;
    case __exchange_sort:
        passed = 0 == test_sort(exchange_sort, true);
        break;
    case __insertion_sort:
        passed = 0 == test_sort(insertion_sort, true);
        break;
    case __selection_sort:
        passed = 0 == test_sort(selection_sort, true);
        break;
    case __merge_sort:
        passed = 0 == test_sort(merge_sort, true);
        break;
    case __quick_sort:
        passed = 0 == test_sort(quick_sort, true);
        break;
    case invalid:
    default:
        break;
    }
    
    if (passed)
        printf("passed!\n");
    else
        printf("failed!\n");

    return passed;
}
