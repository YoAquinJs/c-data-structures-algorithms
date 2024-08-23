#include <stdio.h>

int bsearch(int n, int* arr, int key){
    int l=0, r=n-1, mid;

    while(l <= r){
        mid = (l+r)/2;

        if (arr[mid] == key)
            return mid;
        else if (arr[mid] < key)
            r = mid-1;
        else
            l = mid+1;
    }

    return -1;
}

int _recursive_bsearch(int* arr, int key, int l, int r){
    int mid = (l+r)/2;

    if (arr[mid] == key)
        return mid;
    if (l == r)
        return arr[mid] == key ? mid : -1;

    if (arr[mid] < key)
        return _recursive_bsearch(arr, key, l, mid-1);
    return _recursive_bsearch(arr, key, mid+1, r);
}

int recursive_bsearch(int n, int* arr, int key){
    return _recursive_bsearch(arr, key, 0, n);
}

int main(){
    if ()
    return 0;
}
