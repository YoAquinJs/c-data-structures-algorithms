#include "sorting.h"

#include <stdlib.h>
#include <string.h>

#include "utils/utils.h"

bool InsertionSort(void* buffer, size_t memb_size, size_t size,
                   Compare compare) {
    if (size == 0) return true;

    void* key = malloc(memb_size);
    if (!key) return false;

    size_t j;
    for (size_t i = 1; i < size; i++) {
        memcpy(key, INDEX(buffer, i, memb_size), memb_size);

        j = i;

        while (j-- > 0 && compare(INDEX(buffer, j, memb_size), key) > 0) {
            memcpy(INDEX(buffer, j + 1, memb_size), INDEX(buffer, j, memb_size),
                   memb_size);
        }

        memcpy(INDEX(buffer, j + 1, memb_size), key, memb_size);
    }
    return true;
}
