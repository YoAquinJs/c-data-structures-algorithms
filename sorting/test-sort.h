#pragma once
#include <stdbool.h>

typedef void(Sort)(int, int*);
int TestSort(Sort sort, bool ascendant);

int TestSelectionSort();
int TestInsertionSort();
int TestExchangeSort();
int TestBubbleSort();
int TestMergeSort();
int TestQuickSort();
