#include "searching.h"

int BinarySearch(int n, int* arr, int key) {
    if (n == 0) return -1;

    int l = 0, r = n - 1, mid;

    while (l <= r) {
        mid = l + (r - l) / 2;

        if (arr[mid] == key) return mid;
        if (arr[mid] < key)
            l = mid + 1;
        else
            r = mid - 1;
    }

    return -1;
}

int RecursiveBSearchRecurion(int* arr, int key, int l, int r) {
    if (l > r) return -1;

    int mid = l + (r - l) / 2;

    if (arr[mid] == key) return mid;

    if (arr[mid] < key) return RecursiveBSearchRecurion(arr, key, mid + 1, r);
    return RecursiveBSearchRecurion(arr, key, l, mid - 1);
}

int RecursiveBsearch(int n, int* arr, int key) {
    if (n == 0) return -1;
    return RecursiveBSearchRecurion(arr, key, 0, n - 1);
}
