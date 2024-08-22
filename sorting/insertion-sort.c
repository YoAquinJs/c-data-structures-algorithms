#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <limits.h>

#include "../utils/utils.h"

int* insertion_sort_ascd(int n, int *arr)
{
    if (n == 0)
        return arr;

    int i, j, key;
    for (i = 1; i < n; i++)
    {
        key = arr[i];
        j = i - 1;
        while (j > -1 && arr[j] > key)
        {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }

    return arr;
}

int* insertion_sort_desc(int n, int *arr){
    if (n == 0)
        return arr;

    int i, j, key;
    for (i = 1; i < n; i++)
    {
        key = arr[i];
        j = i - 1;
        while (j > -1 && arr[j] < key)
        {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }

    return arr;
}

// gcc insertion-sort.c ../utils/*.c -o main; ./main
int main()
{
    if (test_sort(insertion_sort_ascd, true, true) == 0)
        printf("passed ascendant!\n");

    if (test_sort(insertion_sort_desc, true, false) == 0)
        printf("passed descendant!\n");

    return 0;
}
