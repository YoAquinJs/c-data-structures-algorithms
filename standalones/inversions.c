/*
implementation for excersice 2,1-5

make inversions
make run TARGET=inversions
*/

#include <stdio.h>
#include <stdlib.h>

int merge(int* arr, int* buff, int left, int mid, int rigth){
    int result=0, left_count = mid-left+1;
    int _left, _rigth, arr_ptr;

    //copy left and rigth to buff
    for (_left=left; _left <= mid; _left++)
        buff[_left] = arr[_left];
    for (_rigth=mid+1; _rigth <= rigth; _rigth++)
        buff[_rigth] = arr[_rigth];

    arr_ptr = left;
    _left = left;
    _rigth = mid+1;

    //merge left and rigth
    while(_left <= mid && _rigth <= rigth){
        if (buff[_rigth] < buff[_left]){
            result += left_count;
            arr[arr_ptr] = buff[_rigth++];
        }else{
            left_count--;
            arr[arr_ptr] = buff[_left++];
        }
        arr_ptr++;
    }
    while(_left <= mid)
        arr[arr_ptr++] = buff[_left++];
    while(_rigth <= mid)
        arr[arr_ptr++] = buff[_rigth++];

    return result;
}

int num_inversions(int* arr, int* buff, int left, int rigth){
    if (left >= rigth)
        return 0;

    int result = 0;

    int mid = left + (rigth-left)/2;
    result += num_inversions(arr, buff, left, mid);
    result += num_inversions(arr, buff, mid+1, rigth);
    result += merge(arr, buff, left, mid, rigth);

    return result;
}

//as a sideeffect sorts arr
int numInversions(int n, int* arr){
    int* buff = malloc(sizeof(int)*n);
    int result = num_inversions(arr, buff, 0, n-1);
    free(buff);
    return result;
}

int main(){
    int arr[] = {1, 4, 5, 3, 2};
    int n = sizeof(arr)/sizeof(int);
    int inversions = numInversions(n, arr);

    printf("expected inversions: 5\n");
    printf("result: %d\n", inversions);

    return 0;
}

