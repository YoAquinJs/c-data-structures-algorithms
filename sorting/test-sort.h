#pragma once
#include <stdbool.h>

typedef void (Sort)(int, int*);
int test_sort(Sort sort, bool ascendant);

void selection_sort(int n, int* arr);
void insertion_sort(int n, int *arr);
void exchange_sort(int n, int* arr);
void bubble_sort(int n, int* arr);
void merge_sort(int n, int* arr);
void quick_sort(int n, int* arr);
