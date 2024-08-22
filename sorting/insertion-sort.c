#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <limits.h>

#include "../utils/utils.h"

int* insertion_sort(int n, int* arr){
    if (n == 0)
        return arr;

    int i, j, key;
    for (i=1; i < n; i++){
        key = arr[i];
        j = i - 1;
        while (j > -1 && arr[j] > key){
            arr[j+1] = arr[j];
            j--;
        }
        arr[j+1] = key;
    }

    return arr;
}

//gcc insertion-sort.c ../utils/*.c -o main; ./main
int main(){
    int passed = test_sort(insertion_sort, true);

    if (passed == 0)
        printf("passed!\n");

    return 0;
}