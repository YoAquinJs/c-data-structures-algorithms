#include "test-sort.h"

int Partition(int* arr, int left, int right) {
    int pivot = arr[right];

    int i = left - 1, j, tmp;
    for (j = left; j < right; j++) {
        if (arr[j] >= pivot) continue;
        i++;
        tmp = arr[i];
        arr[i] = arr[j];
        arr[j] = tmp;
    }

    tmp = arr[i + 1];
    arr[i + 1] = arr[right];
    arr[right] = tmp;
    return i + 1;
}

void QuickSortRecursion(int* arr, int left, int right) {
    if (left >= right) return;

    int pivot = Partition(arr, left, right);
    QuickSortRecursion(arr, left, pivot - 1);
    QuickSortRecursion(arr, pivot + 1, right);
}

void QuickSort(int n, int* arr) {
    if (n < 1) return;
    QuickSortRecursion(arr, 0, n - 1);
}

int TestQuickSort() {
    return TestSort(QuickSort, true);
}
