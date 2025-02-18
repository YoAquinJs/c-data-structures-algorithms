#include "searching.h"

#include "utils/utils.h"

void* LinearSearch(void* buffer, size_t memb_size, size_t size, Compare compare,
                   void* memb) {
    if (size == 0) return NULL;

    void* max = INDEX(buffer, size, memb_size);

    for (; buffer < max; INDEX(buffer, 1, memb_size)) {
        if (compare(buffer, memb) == 0) return buffer;
    }

    return NULL;
}
