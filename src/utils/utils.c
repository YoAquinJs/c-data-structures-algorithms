#include "utils.h"

#include <stdio.h>
#include <string.h>

void swap(void* buffer, size_t memb_size, size_t a, size_t b) {
    if (a == b) return;

    unsigned char* base = (unsigned char*)buffer;
    unsigned char* p1 = base + (a * memb_size);
    unsigned char* p2 = base + (b * memb_size);

    unsigned char buf[64];

    if (memb_size <= sizeof(buf)) {
        memcpy(buf, p1, memb_size);
        memcpy(p1, p2, memb_size);
        memcpy(p2, buf, memb_size);
        return;
    }

    for (size_t i = 0; i < memb_size; i++) {
        unsigned char t = p1[i];
        p1[i] = p2[i];
        p2[i] = t;
    }
}
