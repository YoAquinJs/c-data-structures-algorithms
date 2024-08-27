#include <stdio.h>
#include <stdbool.h>

#include "test.h"
#include "../utils/utils.h"

void exchange_sort_ascd(int n, int* arr){
    if (n == 0)
        return;

    int tmp;
    for (int i=0; i < n-1; i++){
        for (int j=i+1; j < n; j++){
            if (arr[i] > arr[j]){
                tmp = arr[i];
                arr[i] = arr[j];
                arr[j] = tmp;
            }
        }
    }
}

void exchange_sort_desc(int n, int* arr){
    if (n == 0)
        return;

    int tmp;
    for (int i=0; i < n-1; i++){
        for (int j=i+1; j < n; j++){
            if (arr[i] < arr[j]){
                tmp = arr[i];
                arr[i] = arr[j];
                arr[j] = tmp;
            }
        }
    }
}

// gcc insertion-sort.c test.c ../utils/*.c -o main; ./main
int main(){
    set_rand_seed();

    if (test_sort(exchange_sort_ascd, true) == 0)
        printf("passed ascendant!\n");

    if (test_sort(exchange_sort_desc, false) == 0)
        printf("passed descendant!\n");

    return 0;
}
