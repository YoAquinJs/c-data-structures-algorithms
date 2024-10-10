#include "test-sort.h"

void InsertionSort(int n, int *arr) {
    if (n == 0) return;

    int i, j, key;
    for (i = 1; i < n; i++) {
        key = arr[i];
        j = i - 1;
        while (j > -1 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

void InsertionSortDesc(int n, int *arr) {
    if (n == 0) return;

    int i, j, key;
    for (i = 1; i < n; i++) {
        key = arr[i];
        j = i - 1;
        while (j > -1 && arr[j] < key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

void RecursiveInsertionSort(int n, int *arr) {
    if (n < 1) return;

    RecursiveInsertionSort(n - 1, arr);

    int key = arr[n - 1], j = n - 2;
    while (j > -1 && arr[j] > key) {
        arr[j + 1] = arr[j];
        j--;
    }
    arr[j + 1] = key;
}

int TestInsertionSort() {
    return TestSort(InsertionSort, true);
}
