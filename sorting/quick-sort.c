#include "test-sort.h"

int partition(int* arr, int left, int rigth){
    int pivot = arr[rigth];

    int i=left-1, j, tmp;
    for (j=left; j < rigth; j++){
        if (arr[j] >= pivot)
            continue;
        i++;
        tmp = arr[i];
        arr[i] = arr[j];
        arr[j] = tmp;
    }

    tmp = arr[i+1];
    arr[i+1] = arr[rigth];
    arr[rigth] = tmp;
    return i+1;
}

void _quick_sort(int* arr, int left, int rigth){
    if (left >= rigth)
        return;

    int pivot = partition(arr, left, rigth);
    _quick_sort(arr, left, pivot-1);
    _quick_sort(arr, pivot+1, rigth);
}

void quick_sort(int n, int* arr){
    if (n < 1)
        return;
    _quick_sort(arr, 0, n-1);
}

int test_quick_sort() { return test_sort(quick_sort, true); }
