#ifndef SEARCHING_H
#define SEARCHING_H

#include <stddef.h>

#include "utils/utils.h"

void* LinearSearch(void* buffer, size_t memb_size, size_t size, Compare compare,
                   void* memb);

void* BinarySearch(void* buffer, size_t memb_size, size_t size, Compare compare,
                   void* memb);

#endif /* ifndef SEARCHING_H */
