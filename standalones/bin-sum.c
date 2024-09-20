/*
implementation for excersice 2,1-5

make bin-sum
make run TARGET=bin-sum
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <memory.h>
#include <inttypes.h>

#define BITS_IN_BYTE 8
#define bitblock_bits sizeof(bitblock)*BITS_IN_BYTE

typedef int8_t bitblock;
typedef struct{
    bitblock* bits;
    size_t len;
    size_t blocks;
} Bitset;

void bset_clear(Bitset* bitset){
    memset(bitset->bits, 0, sizeof(bitblock)*bitset->blocks);
}

Bitset* new_bitset(size_t len){
    if (len < 1)
        return NULL;

    div_t len_div = div(len, bitblock_bits);
    size_t blocks = len_div.quot + (len_div.rem==0 ? 0 : 1);
    bitblock* bits = calloc(blocks, sizeof(bitblock));
    if (!bits)
        return NULL;

    Bitset* bitset = malloc(sizeof(Bitset));
    bitset->bits = bits;
    bitset->blocks = blocks;
    bitset->len = len;
    return bitset;
}

Bitset* int_to_bset(int num){
    size_t blocks = sizeof(num);
    bitblock* bits = malloc(blocks*sizeof(bitblock));
    if (!bits)
        return NULL;

    bits[0] = num & 0x000000ff;
    bits[1] = (num & 0x0000ff00) >> 8;
    bits[2] = (num & 0x00ff0000) >> 16;
    bits[3] = (num & 0xff000000) >> 24;
    Bitset* bitset = malloc(sizeof(Bitset));
    bitset->bits = bits;
    bitset->blocks = blocks;
    bitset->len = blocks*BITS_IN_BYTE;
    return bitset;
}

void free_bset(Bitset* bitset){
    free(bitset->bits);
    free(bitset);
}

bool bset_getn(Bitset* bitset, size_t n){
    if (n >= bitset->len)
        return 0;

    div_t n_div = div(n, bitblock_bits);
    return (bitset->bits[n_div.quot] >> n_div.rem) & 1;
}

void bset_setn(Bitset* bitset, size_t n, bool bit){
    if (n >= bitset->len)
        return;

    div_t n_div = div(n, bitblock_bits);

    if (bit)
        bitset->bits[n_div.quot] |= (1<<n_div.rem);
    else
        bitset->bits[n_div.quot] &= ~(1<<n_div.rem);
}

char* str_bset(Bitset* bitset){
    size_t p=0;
    char* str = malloc(bitset->len*sizeof(char) + 1);
    bitblock ptr;
    bitblock max_bit = (bitblock)1 << (bitblock_bits-1);

    for (size_t i=0; i < bitset->blocks; i++){
        ptr = 1;
        while(p < bitset->len){
            str[p++] = '0'+((bitset->bits[i] & ptr) > 0 ? 1 : 0);
            if (ptr == max_bit)
                break;
            ptr <<= 1;
        }
    }

    str[p] = '\0';
    return str;
}

Bitset* bin_sum(Bitset* num1, Bitset* num2){
    if (num1->len != num2->len)
        return NULL;

    Bitset* result = new_bitset(num1->len+1);
    if (!result)
        return NULL;

    int carry = 0;
    size_t i;
    for (i=0; i < num1->len; i++){
        carry += bset_getn(num1, i) + bset_getn(num2, i);
        if (carry & 1){
            carry = 0;
            bset_setn(result, i, 1);
        }
        if (carry > 1)
            carry = 1;
    }

    bset_setn(result, i, carry);
    return result;
}

int main(){
    Bitset* num1 = int_to_bset(5);
    Bitset* num2 = int_to_bset(3);
    Bitset* sum = bin_sum(num1, num2);

    char* num1_str = str_bset(num1);
    printf("%s\n", num1_str);
    char* num2_str = str_bset(num2);
    printf("%s\n", num2_str);
    char* sum_str = str_bset(sum);
    printf("%s\n", sum_str);

    free_bset(num1);
    free_bset(num2);
    free_bset(sum);
    free(sum_str);
    return 0;
}

