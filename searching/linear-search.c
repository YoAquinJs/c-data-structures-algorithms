#include <stdio.h>
#include <stdlib.h>

#include "test.h"
#include "../utils/utils.h"

int linear_search(int n, int* arr, int elem){
    for (int i=0; i < n; i++){
        if (arr[i] == elem)
            return i;
    }
    return -1;
}

// gcc linear-search.c test.c ../utils/*.c -o main; ./main
int main(){
    set_rand_seed();

    if (test_search(linear_search) == 0)
        printf("passed linear search\n");

    return 0;
}
