#include "test-search.h"

int binary_search(int n, int* arr, int key){
    if (n == 0)
        return -1;

    int l=0, r=n-1, mid;

    while(l <= r){
        mid = l + (r-l)/2;

        if (arr[mid] == key)
            return mid;
        if (arr[mid] < key)
            l = mid+1;
        else
            r = mid-1;
    }

    return -1;
}

int _recursive_bsearch(int* arr, int key, int l, int r){
    if (l > r)
        return -1;

    int mid = l + (r-l)/2;

    if (arr[mid] == key)
        return mid;

    if (arr[mid] < key)
        return _recursive_bsearch(arr, key, mid+1, r);
    return _recursive_bsearch(arr, key, l, mid-1);
}

int recursive_bsearch(int n, int* arr, int key){
    if (n == 0)
        return -1;
    return _recursive_bsearch(arr, key, 0, n-1);
}

int test_binary_search() { return test_search(binary_search); }
