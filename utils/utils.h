#pragma once

#define rand_half RAND_MAX/2

void set_rand_seed();

int cmp_ascd(const void *a, const void *b);
int cmp_desc(const void *a, const void *b);

int* cp_arr(int n, int* arr);
void print_arr(int n, int* arr);

int* random_arr(int n);
int* sorted_arr(int n, bool ascendant, int first);
