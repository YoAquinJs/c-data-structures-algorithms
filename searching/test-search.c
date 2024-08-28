#include <stdlib.h>
#include <stdio.h>
#include <limits.h>

#include "test-search.h"
#include "../test-map.h"
#include "../utils/utils.h"

#define MAX_ARR_N 1000
#define TESTS 1000

bool test_key_search(int* arr, int* expected, int attempted, int key){
    if (!expected && attempted != -1)
        return false;
    if (expected && (attempted == -1 || arr[attempted] != key))
        return false;
    return true;
}

int test_search(Search search){
    int tests_left = TESTS;
    int* tests = generate_test_sizes(tests_left, MAX_ARR_N);
    if (!tests)
        return tests_left;

    int *arr, *arr_copy;
    int *expected, attempted, key, n;
    for (tests_left--; tests_left > -1; tests_left--){
        n = tests[tests_left];
        arr = sorted_arr(n, true, rand() - rand_half);
        arr_copy = cp_arr(n, arr);
        if (!arr && n > 0){
            free(tests);
            return tests_left+1;
        }

        key = INT_MIN;
        expected =(int*) bsearch(&key, arr, n, sizeof(int), cmp_ascd);
        attempted = search(n, arr_copy, key);
        if (!test_key_search(arr, expected, attempted, key))
            break;

        key = INT_MAX;
        expected =(int*) bsearch(&key, arr, n, sizeof(int), cmp_ascd);
        attempted = search(n, arr_copy, key);
        if (!test_key_search(arr, expected, attempted, key))
            break;

        key = get_rand_in_array(n, arr);
        expected =(int*) bsearch(&key, arr, n, sizeof(int), cmp_ascd);
        attempted = search(n, arr_copy, key);
        if (!test_key_search(arr, expected, attempted, key))
            break;

        free(arr);
        free(arr_copy);
    }

    free(tests);
    if (tests_left == -1)
        return 0;

    if (PRINT_ON_FAIL){
        printf("algorithm failed, size: %d\n", n);
        printf("failed on:\n");
        print_arr(n, arr);
        printf("attempted: %d\n", attempted);
        printf("expected: %d \n", expected ? *expected : -1);
    }

    free(arr);
    free(arr_copy);
    return tests_left+1;
}
