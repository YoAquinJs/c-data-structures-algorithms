#include "utils.h"

#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void SetRandSeed() {
    srand(time(0));
}

int GetRandInRange(int a, int b) {
    if (b < a) {
        printf("invalid range\n");
        return 0;
    }

    if (a == b) return a;

    return a + (rand() % (b - a + 1));
}

int GetRandInArray(int n, int* arr) {
    if (!arr) return 0;
    return GetRandInRange(arr[0], arr[n - 1]);
}

int CmpAscd(const void* a, const void* b) {
    return *(int*)a - *(int*)b;
}

int CmpDesc(const void* a, const void* b) {
    return *(int*)b - *(int*)a;
}

bool IsSorted(int n, int* original_arr, int* arr, bool ascendant) {
    qsort(original_arr, n, sizeof(int), ascendant ? CmpAscd : CmpDesc);

    for (int i = 0; i < n; i++) {
        if (original_arr[i] != arr[i]) return false;
    }

    return true;
}

int* RandomArr(int n) {
    if (n < 1) return NULL;

    int* arr = malloc(sizeof(int) * n);
    if (!arr) {
        printf("unable to allocate random arr\n");
        return NULL;
    }

    for (int i = 0; i < n; i++) arr[i] = rand() - rand_half;

    return arr;
}

int* SortedArr(int n, bool ascendant, int first) {
    if (n < 1) return NULL;

    const int num_max_dist = 100;

    int* arr = malloc(sizeof(int) * n);
    if (!arr) {
        printf("unable to allocate sorted arr\n");
        return NULL;
    }

    arr[0] = first;

    int sign = ascendant ? 1 : -1;
    int i, next;
    for (i = 1; i < n; i++) {
        if (__builtin_add_overflow(arr[i - 1], sign * (rand() % num_max_dist),
                                   &next))
            break;
        arr[i] = next;
    }

    if (i == n) return arr;

    int left = ascendant ? INT_MAX : INT_MIN;
    for (; i < n; i++) arr[i] = left;

    return arr;
}

int* CpArr(int n, int* arr) {
    if (n < 1 || !arr) return NULL;

    int* cp = malloc(sizeof(int) * n);
    if (!cp) {
        printf("unable to allocate cp_arr\n");
        return NULL;
    }

    for (n--; n > -1; n--) cp[n] = arr[n];

    return cp;
}

void PrintArr(int n, int* arr) {
    if (n < 1) {
        printf("[]\n");
        return;
    }

    printf("[ %d", arr[0]);

    const int col_size = 4;
    int col = 1;
    for (int i = 1; i < n; i++) {
        col++;
        printf(",\t%d", arr[i]);

        if (col % col_size != 0) continue;

        i++;
        if (i >= n) break;

        col++;
        printf(",\n  %d", arr[i]);
    }

    printf(" ]\n");
}

int* GenerateTestSizes(int count, int max) {
    if (count < 6) {
        printf("too few tests");
        return NULL;
    }

    int* tests = malloc(sizeof(int) * count);
    if (!tests) {
        printf("unable to allocate tests_sizes\n");
        return NULL;
    }

    tests[0] = 0;
    tests[1] = 1;
    tests[2] = 2;
    tests[--count] = max;
    tests[--count] = max - 1;
    tests[--count] = max - 2;

    int dist = count / (max - 6);
    for (int i = 3; i < count; i++) tests[i] = tests[i - 1] + dist;

    return tests;
}

int BenchmarkTest(int (*func)(void)) {
    clock_t start, end;
    double cpu_time_used;

    start = clock();
    int missing_tests = func();
    end = clock();

    cpu_time_used = ((double)(end - start)) * 1000 / CLOCKS_PER_SEC;
    printf("Time taken: %f ms\n", cpu_time_used);
    return missing_tests;
}
