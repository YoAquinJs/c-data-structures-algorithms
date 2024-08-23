#include <time.h>
#include <stdio.h>
#include <stdlib.h>

#include "utils.h"

void set_rand_seed(){
    srand(time(0));
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
