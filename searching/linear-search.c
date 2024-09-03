#include "test-search.h"

int linear_search(int n, int* arr, int elem){
    for (int i=0; i < n; i++){
        if (arr[i] == elem)
            return i;
    }
    return -1;
}

int test_linear_search() { return test_search(linear_search); }
