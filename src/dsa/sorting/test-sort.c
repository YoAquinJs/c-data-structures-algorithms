#include "test-sort.h"

#include <stdio.h>
#include <stdlib.h>

#include "../../utils/utils.h"
#include "../test-map.h"

#define MAX_ARR_N 1000
#define TESTS 1000

int TestSort(Sort sort, bool ascendant) {
    int tests_left = TESTS;
    int* tests = GenerateTestSizes(tests_left, MAX_ARR_N);
    if (!tests) return tests_left;

    int *arr, *sorted_arr, *attempted, n;
    for (tests_left--; tests_left > -1; tests_left--) {
        n = tests[tests_left];
        arr = RandomArr(n);
        sorted_arr = CpArr(n, arr);
        attempted = CpArr(n, arr);
        if (n > 0 && (!arr || !sorted_arr || !attempted)) {
            free(tests);
            return tests_left + 1;
        }

        sort(n, attempted);

        if (!IsSorted(n, sorted_arr, attempted, ascendant)) break;

        free(arr);
        free(sorted_arr);
        free(attempted);
    }

    free(tests);
    if (tests_left == -1) return 0;

    if (PRINT_ON_FAIL) {
        printf("algorithm failed, size: %d\n", n);
        printf("failed on:\n");
        PrintArr(n, arr);
        printf("attempted:\n");
        PrintArr(n, attempted);
        printf("expected:\n");
        PrintArr(n, sorted_arr);
    }

    free(arr);
    free(sorted_arr);
    free(attempted);
    return tests_left + 1;
}
