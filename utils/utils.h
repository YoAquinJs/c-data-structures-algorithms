#include <stdbool.h>

bool is_sorted(int n, int* arr, int* sorted, bool ascendant);
int test_sort(int* (sort)(int, int*), bool inplace, bool ascendant);

int* random_arr(int n);
int* cp_arr(int n, int* arr);

void print_arr(int n, int* arr);
