#pragma once

#include <stdbool.h>
#include <stdint.h>

// a < b <-> int < 0
// a > b <-> int > 0
// a == b <-> int == 0
typedef int8_t (*Compare)(const void*, const void*);
