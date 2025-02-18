#include "sorting.h"

bool SelectionSort(void* buffer, size_t memb_size, size_t size,
                   Compare compare) {
    if (size == 0) return true;

    size_t min;
    for (size_t i = 0; i < size - 1; i++) {
        min = i;
        for (size_t j = i + 1; j < size; j++) {
            if (compare(INDEX(buffer, j, memb_size),
                        INDEX(buffer, min, memb_size)) < 0) {
                min = j;
            }
        }

        swap(buffer, memb_size, i, min);
    }

    return true;
}
