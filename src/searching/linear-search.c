#include "searching.h"

int LinearSearch(int n, int* arr, int elem) {
    for (int i = 0; i < n; i++) {
        if (arr[i] == elem) return i;
    }
    return -1;
}
