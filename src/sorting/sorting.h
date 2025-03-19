#ifndef SORTING_H
#define SORTING_H

#include <stdbool.h>
#include <stddef.h>

#include "utils/utils.h"

// sort function type
// parameters are buffer, member size, size and compare function
typedef bool (*Sort)(void*, size_t, size_t, Compare);

bool ExchangeSort(void* buffer, size_t memb_size, size_t size, Compare compare);

bool BubbleSort(void* buffer, size_t memb_size, size_t size, Compare compare);

bool SelectionSort(void* buffer, size_t memb_size, size_t size,
                   Compare compare);

bool InsertionSort(void* buffer, size_t memb_size, size_t size,
                   Compare compare);

bool MergeSort(void* buffer, size_t memb_size, size_t size, Compare compare);

bool QuickSort(void* buffer, size_t memb_size, size_t size, Compare compare);

#endif /* ifndef SORTING_H */
