#include <stdio.h>
#include <stdbool.h>

#include "test.h"
#include "../utils/utils.h"

void selection_sort_ascd(int n, int* arr){
    if (n == 0)
        return;

    int min, tmp;
    for (int i=0; i < n-1; i++){
        min = i;
        for (int j=i+1; j < n; j++){
            if (arr[j] < arr[min])
                min = j;
        }

        // swap
        tmp = arr[min];
        arr[min] = arr[i];
        arr[i] = tmp;

    }
}

void selection_sort_desc(int n, int* arr){
    if (n == 0)
        return;

    int max, tmp;
    for (int i=0; i < n-1; i++){
        max = i;
        for (int j=i+1; j < n; j++){
            if (arr[j] > arr[max])
                max = j;
        }

        // swap
        tmp = arr[max];
        arr[max] = arr[i];
        arr[i] = tmp;

    }
}

// gcc selection-sort.c test.c ../utils/*.c -o main; ./main
int main(){
    set_rand_seed();

    if (test_sort(selection_sort_ascd, true) == 0)
        printf("passed ascendant!\n");

    if (test_sort(selection_sort_desc, false) == 0)
        printf("passed descendant!\n");

    return 0;
}
