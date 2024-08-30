#include <stdlib.h>

#include "test-sort.h"

void merge(int* arr, int* buff, int left, int mid, int rigth){
    int _left, _rigth, arr_ptr;

    //copy left and rigth to buff
    for (_left=left; _left <= mid; _left++)
        buff[_left] = arr[_left];
    for (_rigth=mid+1; _rigth <= rigth; _rigth++)
        buff[_rigth] = arr[_rigth];

    arr_ptr = left;
    _left = left;
    _rigth = mid+1;

    //merge left and rigth
    while(_left <= mid && _rigth <= rigth)
        arr[arr_ptr++] = buff[_left] < buff[_rigth] ? buff[_left++] : buff[_rigth++];
    while(_left <= mid)
        arr[arr_ptr++] = buff[_left++];
    while(_rigth <= mid)
        arr[arr_ptr++] = buff[_rigth++];
}

void _merge_sort(int* arr, int* buff, int left, int rigth){
    if (left >= rigth)
        return;

    int mid = left + (rigth-left)/2;
    _merge_sort(arr, buff, left, mid);
    _merge_sort(arr, buff, mid+1, rigth);

    merge(arr, buff, left, mid, rigth);
}

void merge_sort(int n, int* arr){
    int* buff = malloc(sizeof(int)*n);
    _merge_sort(arr, buff, 0, n-1);
    free(buff);
}

void test_merge_sort() { test_sort(merge_sort, true); }
