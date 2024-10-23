#pragma once

#include <stdbool.h>
#include <stdint.h>

#define rand_half RAND_MAX / 2

// a < b <-> int < 0
// a > b <-> int > 0
// a == b <-> int == 0
typedef int8_t (*Compare)(const void*, const void*);

void SetRandseed();
int GetRandInRange(int a, int b);
int GetRandInArray(int n, int* arr);

int CmpAscd(const void* a, const void* b);
int CmpDesc(const void* a, const void* b);

int* CpArr(int n, int* arr);
void PrintArr(int n, int* arr);

int* RandomArr(int n);
int* SortedArr(int n, bool ascendant, int first);

bool IsSorted(int n, int* originalArr, int* arr, bool ascendant);

int* GenerateTestSizes(int count, int max);

int BenchmarkTest(int (*func)(void));
