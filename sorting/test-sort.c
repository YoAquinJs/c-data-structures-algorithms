#include <stdio.h>
#include <stdlib.h>

#include "test-sort.h"
#include "../utils/utils.h"

#define MAX_ARR_N 1000
#define TESTS 1000

int test_sort(Sort sort, bool ascendant){
    int tests_left = TESTS;
    int* tests = generate_test_size(tests_left, MAX_ARR_N);
    if (!tests)
        return tests_left;

    int *arr, *sorted_arr, *attempted, n;
    for (tests_left--; tests_left > -1; tests_left--){
        n = tests[tests_left];
        arr = random_arr(n);
        sorted_arr = cp_arr(n, arr);
        attempted = cp_arr(n, arr);
        if (n > 0 && (!arr || !sorted_arr || !attempted)){
            free(tests);
            return tests_left+1;
        }

        sort(n, attempted);

        if (!is_sorted(n, sorted_arr, attempted, ascendant))
            break;

        free(arr);
        free(sorted_arr);
        free(attempted);
    }

    free(tests);
    if (tests_left == -1)
        return 0;

    printf("failed on:\n");
    print_arr(n, arr);
    printf("attempted:\n");
    print_arr(n, attempted);
    printf("expected:\n");
    print_arr(n, sorted_arr);
    printf("algorithm failed, size: %d\n", n);
    printf("missing tests %d\n\n", tests_left);

    free(arr);
    free(sorted_arr);
    free(attempted);

    return tests_left;
}
