#include "sorting.h"

bool BubbleSort(void* buffer, size_t memb_size, size_t size, Compare compare) {
    if (size == 0) return true;

    bool sorted;
    for (size_t i = 0; i < size - 1; i++) {
        sorted = true;
        for (size_t j = 0; j < size - i - 1; j++) {
            if (compare(INDEX(buffer, j, memb_size),
                        INDEX(buffer, j + 1, memb_size)) <= 0) {
                continue;
            }

            sorted = false;
            swap(buffer, memb_size, j, j + 1);
        }

        if (sorted) break;
    }

    return true;
}
