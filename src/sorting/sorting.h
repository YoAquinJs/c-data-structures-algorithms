#pragma once

#include <stdbool.h>
#include <stddef.h>

#include "utils/utils.h"

bool ExchangeSort(void* buffer, size_t memb_size, size_t size, Compare compare);

bool BubbleSort(void* buffer, size_t memb_size, size_t size, Compare compare);

bool SelectionSort(void* buffer, size_t memb_size, size_t size,
                   Compare compare);

bool InsertionSort(void* buffer, size_t memb_size, size_t size,
                   Compare compare);

bool MergeSort(void* buffer, size_t memb_size, size_t size, Compare compare);

bool QuickSort(void* buffer, size_t memb_size, size_t size, Compare compare);
