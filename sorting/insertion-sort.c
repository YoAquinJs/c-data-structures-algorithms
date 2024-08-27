#include <stdio.h>
#include <stdbool.h>

#include "test.h"
#include "../utils/utils.h"

void insertion_sort_ascd(int n, int *arr){
    if (n == 0)
        return;

    int i, j, key;
    for (i = 1; i < n; i++){
        key = arr[i];
        j = i - 1;
        while (j > -1 && arr[j] > key){
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

void insertion_sort_desc(int n, int *arr){
    if (n == 0)
        return;

    int i, j, key;
    for (i = 1; i < n; i++){
        key = arr[i];
        j = i - 1;
        while (j > -1 && arr[j] < key){
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

// gcc insertion-sort.c test.c ../utils/*.c -o main; ./main
int main(){
    set_rand_seed();

    if (test_sort(insertion_sort_ascd, true) == 0)
        printf("passed ascendant!\n");

    if (test_sort(insertion_sort_desc, false) == 0)
        printf("passed descendant!\n");

    return 0;
}
