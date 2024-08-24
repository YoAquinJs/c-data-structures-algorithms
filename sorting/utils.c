#include <stdio.h>
#include <stdlib.h>

#include "utils.h"
#include "../utils/utils.h"

#define MAX_ARR_N 1000
#define TESTS 1000

int test_sort(int* (sort)(int, int*), bool inplace, bool ascendant){
    int tests_left = TESTS;
    int* tests = generate_test_size(tests_left, MAX_ARR_N);
    if (!tests)
        return tests_left;

    IsSorted isSorted;
    int *arr, *attempted, n;
    for (tests_left--; tests_left > -1; tests_left--){
        n = tests[tests_left];
        arr = random_arr(n);
        if (!arr)
            return tests_left;

        if (inplace)
            attempted = sort(n, cp_arr(n, arr));
        else
            attempted = sort(n, arr);

        isSorted = is_sorted(n, attempted, ascendant);
        if (!isSorted.expected)
            return tests_left;

        if (!isSorted.sorted)
            break;

        free(arr);
        free(attempted);
        free(isSorted.expected);
    }

    if (isSorted.sorted)
        return 0;

    printf("algorithm failed, size: %d\n", n);
    printf("missing tests %d\n\n", tests_left);
    printf("failed on:\n");
    print_arr(n, arr);
    printf("attempted:\n");
    print_arr(n, attempted);
    printf("expected:\n");
    print_arr(n, isSorted.expected);

    free(arr);
    free(attempted);
    free(isSorted.expected);

    return tests_left;
}
