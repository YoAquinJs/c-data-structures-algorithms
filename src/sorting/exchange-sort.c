#include "sorting.h"

bool ExchangeSort(void* buffer, size_t memb_size, size_t size,
                  Compare compare) {
    if (size == 0) return true;

    for (size_t i = 0; i < size - 1; i++) {
        for (size_t j = i + 1; j < size; j++) {
            if (compare(INDEX(buffer, i, memb_size),
                        INDEX(buffer, j, memb_size)) > 0) {
                swap(buffer, memb_size, i, j);
            }
        }
    }

    return true;
}
