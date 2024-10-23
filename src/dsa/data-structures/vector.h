#pragma once

#include <stdbool.h>
#include <stddef.h>

// capacity increase strategy
// in current capacity out incremented capacity
typedef size_t (*CapacityIncrease)(size_t);

size_t CapacityDouble(size_t capacity);
size_t CapacityBinaryCompleteTree(size_t capacity);

typedef struct Vector {
    void* buffer;
    size_t memb_size;
    size_t size;
    size_t capacity;
    CapacityIncrease capacity_inc;
} Vector;

// trust receiver to check buffer nullness
Vector NewVector(size_t memb_size, size_t capacity,
                 CapacityIncrease capacity_inc);
void FreeVector(Vector* vec);

// bool VectorCheckOverflow(Vector* vec, size_t new_elems);
// int VectorCapacityOverflow(Vector* vec, size_t new_elems);

int VectorIndex(Vector* vec, size_t index, void** elem);

int VectorRemove(Vector* vec, size_t index);
int VectorInsert(Vector* vec, void* elem, size_t index);
void VectorClear(Vector* vec);

int VectorPop(Vector* vec);
int VectorAppend(Vector* vec, void* elem);
