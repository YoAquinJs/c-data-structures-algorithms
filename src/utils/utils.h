#pragma once

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

// a < b <-> int < 0
// a > b <-> int > 0
// a == b <-> int == 0
typedef int8_t (*Compare)(const void*, const void*);

#define INDEX(buffer, i, memb_size) \
    ((void*)((unsigned char*)(buffer) + ((i) * (memb_size))))

// swap elements in a buffer by indexes a and b
void swap(void* buffer, size_t memb_size, size_t a, size_t b);
