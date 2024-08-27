#include <stdio.h>
#include <stdbool.h>

#include "test.h"
#include "../utils/utils.h"

void bubble_sort_ascd(int n, int* arr){
    if (n == 0)
        return;

    int tmp;
    bool sorted;
    for(int i=0; i<n-1; i++){
        sorted = true;
        for (int j=0; j<n-i-1; j++){
            if (arr[j] <= arr[j+1])
                continue;
            sorted = false;
            tmp = arr[j];
            arr[j] = arr[j+1];
            arr[j+1] = tmp;
        }
        if (sorted)
            break;
    }
}

void bubble_sort_desc(int n, int* arr){
    if (n == 0)
        return;

    int tmp;
    bool sorted;
    for(int i=0; i<n-1; i++){
        sorted = true;
        for (int j=0; j<n-i-1; j++){
            if (arr[j] >= arr[j+1])
                continue;
            sorted = false;
            tmp = arr[j];
            arr[j] = arr[j+1];
            arr[j+1] = tmp;
        }
        if (sorted)
            break;
    }
}

// gcc bubble-sort.c test.c ../utils/*.c -o main; ./main
int main(){
    set_rand_seed();

    if (test_sort(bubble_sort_ascd, true) == 0)
        printf("passed ascendant!\n");

    if (test_sort(bubble_sort_desc, false) == 0)
        printf("passed descendant!\n");

    return 0;
}
