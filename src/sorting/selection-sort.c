#include "sorting.h"

void SelectionSort(int n, int* arr) {
    if (n == 0) return;

    int min, tmp;
    for (int i = 0; i < n - 1; i++) {
        min = i;
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[min]) min = j;
        }

        tmp = arr[min];
        arr[min] = arr[i];
        arr[i] = tmp;
    }
}

void SelectionSortDesc(int n, int* arr) {
    if (n == 0) return;

    int max, tmp;
    for (int i = 0; i < n - 1; i++) {
        max = i;
        for (int j = i + 1; j < n; j++) {
            if (arr[j] > arr[max]) max = j;
        }

        tmp = arr[max];
        arr[max] = arr[i];
        arr[i] = tmp;
    }
}
