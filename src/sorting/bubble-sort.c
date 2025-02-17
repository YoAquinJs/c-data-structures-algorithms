#include "sorting.h"

#include <stdbool.h>

void BubbleSort(int n, int* arr) {
    if (n == 0) return;

    int tmp;
    bool sorted;
    for (int i = 0; i < n - 1; i++) {
        sorted = true;
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] <= arr[j + 1]) continue;
            sorted = false;
            tmp = arr[j];
            arr[j] = arr[j + 1];
            arr[j + 1] = tmp;
        }
        if (sorted) break;
    }
}

void BubbleSortDesc(int n, int* arr) {
    if (n == 0) return;

    int tmp;
    bool sorted;
    for (int i = 0; i < n - 1; i++) {
        sorted = true;
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] >= arr[j + 1]) continue;
            sorted = false;
            tmp = arr[j];
            arr[j] = arr[j + 1];
            arr[j + 1] = tmp;
        }
        if (sorted) break;
    }
}
