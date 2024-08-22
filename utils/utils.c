#include <time.h>
#include <stdio.h>
#include <stdlib.h>

#include "utils.h"

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

bool is_sorted(int n, int* sorted_arr, int* sorted, bool ascendant){
    for (int i=0; i < n; i++){
        if (sorted_arr[i] != sorted[i])
            return false;
    }
    return true;
}

int test_sort(int* (sort)(int, int*), bool inplace, bool ascendant){
    srand(time(0));

    int max_n = 10;
    int tests = 1000;
    int *arr, *sorted_arr, *sorted;
    int n;

    for (; tests > 0; tests--){
        n = rand() % max_n;
        arr = random_arr(n);
        sorted_arr = cp_arr(n, arr);
        qsort(sorted_arr, n, sizeof(int), ascendant ? cmp_ascd : cmp_desc);

        if (inplace)
            sorted = sort(n, cp_arr(n, arr));
        else
            sorted = sort(n, arr);

        if (!is_sorted(n, sorted_arr, sorted, ascendant))
            break;

        free(arr);
        free(sorted_arr);
        free(sorted);
        arr = NULL;
    }

    if (!arr)
        return 0;

    printf("algorithm failed size %d\nmissing tests %d\n\n", n, tests);
    print_arr(n, arr);
    printf("sorted:\n");
    print_arr(n, sorted_arr);
    printf("attempt:\n");
    print_arr(n, sorted);

    free(arr);
    free(sorted);
    free(sorted_arr);
    return tests;
}

int* random_arr(int n){
    if (n == 0)
        return NULL;

    #define rand_half RAND_MAX/2
    int* arr = malloc(sizeof(int)*n);
    for (n--; n > -1; n--)
        arr[n] = rand() - rand_half;

    return arr;
}

int* cp_arr(int n, int* arr){
    if (n == 0)
        return NULL;

    int* cp = malloc(sizeof(int)*n);
    for (n--; n > -1; n--)
        cp[n] = arr[n];

    return cp;
}

void print_arr(int n, int* arr){
    if (n == 0){
        printf("[]\n");
        return;
    }

    printf("[ %d", arr[0]);
    const int col_size = 4;
    int col = 1;
    for (int i = 1; i < n; i++){
        printf(",\t%d", arr[i]);
        col++;
        if (col % col_size != 0)
            continue;

        if (i == n-1)
            break;

        i++;
        col++;
        printf(",\n  %d", arr[i]);
    }

    printf(" ]\n");
}
