#include "test-sort.h"

void bubble_sort(int n, int* arr){
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

void test_bubble_sort() { test_sort(bubble_sort, true); }
