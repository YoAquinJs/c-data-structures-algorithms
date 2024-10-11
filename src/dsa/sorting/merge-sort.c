#include <stdlib.h>

#include "test-sort.h"

void Merge(int* arr, int* buff, int left, int mid, int right) {
    int _left, _rigth, arr_ptr;

    // copy left and right to buff
    for (_left = left; _left <= mid; _left++) buff[_left] = arr[_left];
    for (_rigth = mid + 1; _rigth <= right; _rigth++)
        buff[_rigth] = arr[_rigth];

    arr_ptr = left;
    _left = left;
    _rigth = mid + 1;

    // merge left and right
    while (_left <= mid && _rigth <= right)
        arr[arr_ptr++] =
            buff[_left] < buff[_rigth] ? buff[_left++] : buff[_rigth++];
    while (_left <= mid) arr[arr_ptr++] = buff[_left++];
    while (_rigth <= mid) arr[arr_ptr++] = buff[_rigth++];
}

void MergeSortRecursion(int* arr, int* buff, int left, int right) {
    if (left >= right) return;

    int mid = left + (right - left) / 2;
    MergeSortRecursion(arr, buff, left, mid);
    MergeSortRecursion(arr, buff, mid + 1, right);

    Merge(arr, buff, left, mid, right);
}

void MergeSort(int n, int* arr) {
    int* buff = malloc(sizeof(int) * n);
    MergeSortRecursion(arr, buff, 0, n - 1);
    free(buff);
}

int TestMergeSort() {
    return TestSort(MergeSort, true);
}
