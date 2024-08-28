#include "test-sort.h"

void exchange_sort(int n, int* arr){
    if (n == 0)
        return;

    int tmp;
    for (int i=0; i < n-1; i++){
        for (int j=i+1; j < n; j++){
            if (arr[i] > arr[j]){
                tmp = arr[i];
                arr[i] = arr[j];
                arr[j] = tmp;
            }
        }
    }
}

void exchange_sort_desc(int n, int* arr){
    if (n == 0)
        return;

    int tmp;
    for (int i=0; i < n-1; i++){
        for (int j=i+1; j < n; j++){
            if (arr[i] < arr[j]){
                tmp = arr[i];
                arr[i] = arr[j];
                arr[j] = tmp;
            }
        }
    }
}
