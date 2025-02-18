#include "searching.h"

#include "utils/utils.h"

void* BinarySearch(void* buffer, size_t memb_size, size_t size, Compare compare,
                   void* memb) {
    if (size == 0) return NULL;

    size_t l = 0, r = size - 1, mid;

    while (l <= r) {
        mid = l + (r - l) / 2;

        int cmp = compare(INDEX(buffer, mid, memb_size), memb);
        if (cmp == 0) return INDEX(buffer, mid, memb_size);
        if (cmp < 0)
            l = mid + 1;
        else
            r = mid - 1;
    }

    return NULL;
}
