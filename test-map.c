#include <string.h>

#include "test-map.h"
#include "searching/test-search.h"
#include "sorting/test-sort.h"

Category get_category(char* category){
    if (strncmp(category, "searching", 10) == 0)
        return searching;
    if (strncmp(category, "sorting", 8) == 0)
        return sorting;
    return invalid;
}

Test get_test(char* test){
    if (strncmp(test, "linear-search", 14) == 0)
        return _linear_search;
    if (strncmp(test, "binary-search", 14) == 0)
        return _binary_search;
    if (strncmp(test, "bubble-sort", 12) == 0)
        return _bubble_sort;
    if (strncmp(test, "exchange-sort", 14) == 0)
        return _exchange_sort;
    if (strncmp(test, "insertion-sort", 15) == 0)
        return _insertion_sort;
    if (strncmp(test, "selection-sort", 15) == 0)
        return _selection_sort;
    if (strncmp(test, "merge-sort", 11) == 0)
        return _merge_sort;
    return invalid;
}

void run_category(Category category){
    switch (category){
    case searching:
        run_test(_linear_search);
        run_test(_binary_search);
        break;
    case sorting:
        run_test(_bubble_sort);
        run_test(_exchange_sort);
        run_test(_insertion_sort);
        run_test(_selection_sort);
        run_test(_merge_sort);
        break;
    case invalid:
    default:
        break;
    }
}
void run_test(Test test){
    switch (test) {
    case _linear_search:
        test_search(linear_search); // in search/test-search.h
        break;
    case _binary_search:
        test_search(binary_search);
        break;
    case _bubble_sort:
        test_sort(bubble_sort, true);
        break;
    case _exchange_sort:
        test_sort(exchange_sort, true);
        break;
    case _insertion_sort:
        test_sort(insertion_sort, true);
        break;
    case _selection_sort:
        test_sort(selection_sort, true);
        break;
    case _merge_sort:
        // test_sort(merge_sort);
        break;
    case invalid:
    default:
        break;
    }
}
