#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

#include "utils.h"

void set_rand_seed(){
    srand(time(0));
}

int cmp_ascd(const void *a, const void *b) {
    int int_a = *(int *)a;
    int int_b = *(int *)b;
    
    if (int_a < int_b) return -1;
    if (int_a > int_b) return 1;
    return 0;
}

int cmp_desc(const void *a, const void *b) {
    int int_a = *(int *)a;
    int int_b = *(int *)b;
    
    if (int_a < int_b) return 1;
    if (int_a > int_b) return -1;
    return 0;
}

IsSorted is_sorted(int n, int* arr, bool ascendant){
    IsSorted result;
    result.sorted = false;

    int *expected = cp_arr(n, arr);
    result.expected = expected;

    if (!expected)
        return result;

    qsort(expected, n, sizeof(int), ascendant ? cmp_ascd : cmp_desc);

    for (int i=0; i < n; i++){
        if (expected[i] != arr[i])
            return result;
    }

    result.sorted = true;
    return result;
}

int* random_arr(int n){
    if (n < 1)
        return NULL;

    int* arr = malloc(sizeof(int)*n);
    if (!arr){
        printf("unable to allocate random arr\n");
        return NULL;
    }

    for (int i=0; i<n; i++)
        arr[i] = rand() - rand_half;

    return arr;
}

int* sorted_arr(int n, bool ascendant, int first){
    if (n < 1)
        return NULL;

    const int num_max_dist = 100;

    int* arr = malloc(sizeof(int)*n);
    if (!arr){
        printf("unable to allocate sorted arr\n");
        return NULL;
    }

    arr[0] = first;

    int sign = ascendant ? 1 : -1;
    int i, next;
    for (i=1; i < n; i++){
        if (__builtin_add_overflow(arr[i-1], sign*(rand()%num_max_dist), &next))
            break;
        arr[i] = next;
    }

    if (i == n)
        return arr;
 
    int left = ascendant ? INT_MAX : INT_MIN;
    for (; i < n; i++)
        arr[i] = left;

    return arr;
}

int* cp_arr(int n, int* arr){
    if (n < 1)
        return NULL;

    int* cp = malloc(sizeof(int)*n);
    if (!cp){
        printf("unable to allocate cp_arr\n");
        return NULL;
    }

    for (n--; n > -1; n--)
        cp[n] = arr[n];

    return cp;
}

void print_arr(int n, int* arr){
    if (n < 1){
        printf("[]\n");
        return;
    }

    printf("[ %d", arr[0]);

    const int col_size = 4;
    int col = 1;
    for (int i=1; i < n; i++){
        col++;
        printf(",\t%d", arr[i]);

        if (col % col_size != 0)
            continue;

        i++;
        if (i >= n)
            break;

        col++;
        printf(",\n  %d", arr[i]);
    }

    printf(" ]\n");
}

int* generate_test_size(int count, int max){
    if (count < 6){
        printf("too few tests");
        return NULL;
    }

    int* tests = malloc(sizeof(int)*count);
    if (!tests){
        printf("unable to allocate tests_sizes\n");
        return NULL;
    }

    tests[0] = 0;
    tests[1] = 1;
    tests[2] = 2;
    tests[--count] = max;
    tests[--count] = max-1;
    tests[--count] = max-2;

    int dist = (max-6)/count;
    for (int i=3; i < count; i++)
        tests[i] = tests[i-1]+dist;

    return tests;
}
