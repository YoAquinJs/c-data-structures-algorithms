#include "sorting.h"

#include <stdlib.h>
#include <string.h>

#include "utils/utils.h"

void QuickSortRecursion(void* buffer, void* pivot_buf, size_t memb_size,
                        Compare compare, size_t left, size_t right) {
    if (left >= right) return;

    // partition

    // copy pivot
    memcpy(pivot_buf, INDEX(buffer, right, memb_size), memb_size);

    size_t i = left - memb_size;
    for (size_t j = left; j < right; j++) {
        if (compare(INDEX(buffer, j, memb_size), pivot_buf) > 0) {
            continue;
        }

        i++;
        swap(buffer, memb_size, i, j);
    }

    // pivot last position
    i++;
    swap(buffer, memb_size, i, right);

    QuickSortRecursion(buffer, pivot_buf, memb_size, compare, left, i - 1);
    QuickSortRecursion(buffer, pivot_buf, memb_size, compare, i + 1, right);
}

bool QuickSort(void* buffer, size_t memb_size, size_t size, Compare compare) {
    if (size == 0) return true;

    void* pivot_buf = malloc(memb_size);
    if (!pivot_buf) return false;

    QuickSortRecursion(buffer, pivot_buf, memb_size, compare, 0, size - 1);
    return true;
}
