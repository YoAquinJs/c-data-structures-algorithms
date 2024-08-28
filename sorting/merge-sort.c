#include <stdlib.h>

#include "test-sort.h"

void merge(int* arr, int* buff, int p, int q, int r){
    int _p, _r, k;
    for (_p=p; _p <= q; _p++)
        buff[_p] = arr[_p];
    for (_r=q+1; _r <= r; _r++)
        buff[_r] = arr[_r];

    k = p;
    _p = p;
    _r = q+1;

    while(_p <= q && _r <= r)
        arr[k++] = buff[_p] < buff[_r] ? buff[_p++] : buff[_r++];

    while(_p <= q)
        arr[k++] = buff[_p++];

    while(_r <= q)
        arr[k++] = buff[_r++];
}

void _merge_sort(int* arr, int* buff, int p, int r){
    if (p >= r)
        return;

    int q = p + (r-p)/2;
    _merge_sort(arr, buff, p, q);
    _merge_sort(arr, buff, q+1, r);

    merge(arr, buff, p, q, r);
}

void merge_sort(int n, int* arr){
    int* buff = malloc(sizeof(int)*n);
    _merge_sort(arr, buff, 0, n-1);
    free(buff);
}
