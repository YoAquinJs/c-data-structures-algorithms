#include "sorting.h"

#include <stdlib.h>
#include <string.h>

void Merge(void* buffer, void* buffer_cp, size_t memb_size, Compare compare,
           size_t left, size_t mid, size_t right) {
    // copy left and right to buffer_cp
    memcpy(INDEX(buffer_cp, left, memb_size), INDEX(buffer, left, memb_size),
           (1 + mid - left) * memb_size);
    memcpy(INDEX(buffer_cp, mid + 1, memb_size),
           INDEX(buffer, mid + 1, memb_size), (right - mid) * memb_size);

    void* buffer_ptr = INDEX(buffer, left, memb_size);
    size_t _left = left, _right = mid + 1;

    // merge left and right
    while (_left <= mid && _right <= right) {
        if (compare(INDEX(buffer_cp, _left, memb_size),
                    INDEX(buffer_cp, _right, memb_size)) < 0) {
            memcpy(buffer_ptr, INDEX(buffer_cp, _left, memb_size), memb_size);
        } else {
            memcpy(buffer_ptr, INDEX(buffer_cp, _right, memb_size), memb_size);
        }
        buffer_ptr = INDEX(buffer_ptr, 1, memb_size);
    }

    if (_left < mid) {
        memcpy(buffer_ptr, INDEX(buffer_cp, _left, memb_size),
               (1 + mid - _left) * memb_size);
    } else {
        memcpy(buffer_ptr, INDEX(buffer_cp, _right, memb_size),
               (right - mid) * memb_size);
    }
}

void MergeSortRecursion(void* buffer, void* buffer_cp, size_t memb_size,
                        Compare compare, size_t left, size_t right) {
    if (left >= right) return;

    size_t mid = left + (right - left) / 2;
    MergeSortRecursion(buffer, buffer_cp, memb_size, compare, left, mid);
    MergeSortRecursion(buffer, buffer_cp, memb_size, compare, mid + 1, right);

    Merge(buffer, buffer_cp, memb_size, compare, left, mid, right);
}

bool MergeSort(void* buffer, size_t memb_size, size_t size, Compare compare) {
    void* buffer_cp = malloc(size * memb_size);
    if (!buffer_cp) return false;

    MergeSortRecursion(buffer, buffer_cp, memb_size, compare, 0, size - 1);

    free(buffer_cp);
    return true;
}
