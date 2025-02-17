/*
implementation for excersice 2,1-5

make inversions
make run TARGET=inversions
*/

#include <stdio.h>
#include <stdlib.h>

int merge(int* arr, int* buff, int left, int mid, int right) {
    int result = 0, left_count = mid - left + 1;
    int _left, _rigth, arr_ptr;

    // copy left and right to buff
    for (_left = left; _left <= mid; _left++) buff[_left] = arr[_left];
    for (_rigth = mid + 1; _rigth <= right; _rigth++)
        buff[_rigth] = arr[_rigth];

    arr_ptr = left;
    _left = left;
    _rigth = mid + 1;

    // merge left and right
    while (_left <= mid && _rigth <= right) {
        if (buff[_rigth] < buff[_left]) {
            result += left_count;
            arr[arr_ptr] = buff[_rigth++];
        } else {
            left_count--;
            arr[arr_ptr] = buff[_left++];
        }
        arr_ptr++;
    }
    while (_left <= mid) arr[arr_ptr++] = buff[_left++];
    while (_rigth <= mid) arr[arr_ptr++] = buff[_rigth++];

    return result;
}

int num_inversions(int* arr, int* buff, int left, int right) {
    if (left >= right) return 0;

    int result = 0;

    int mid = left + (right - left) / 2;
    result += num_inversions(arr, buff, left, mid);
    result += num_inversions(arr, buff, mid + 1, right);
    result += merge(arr, buff, left, mid, right);

    return result;
}

// as a sideeffect sorts arr
int numInversions(int n, int* arr) {
    int* buff = malloc(sizeof(int) * n);
    int result = num_inversions(arr, buff, 0, n - 1);
    free(buff);
    return result;
}
