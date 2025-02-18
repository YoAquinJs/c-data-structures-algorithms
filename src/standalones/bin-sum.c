/*
Introduction to Algorithms
implementation for excersice 2,1-5
*/

#include "bin-sum.h"

#include <memory.h>
#include <stdlib.h>

void BitsetClear(Bitset* bitset) {
    memset(bitset->bits, 0, sizeof(bit_block) * bitset->blocks);
}

Bitset* NewBitset(size_t len) {
    if (len < 1) return NULL;

    div_t len_div = div(len, BITS_IN_BLOCK);
    size_t blocks = len_div.quot + (len_div.rem == 0 ? 0 : 1);
    bit_block* bits = calloc(blocks, sizeof(bit_block));
    if (!bits) return NULL;

    Bitset* bitset = malloc(sizeof(Bitset));
    bitset->bits = bits;
    bitset->blocks = blocks;
    bitset->len = len;
    return bitset;
}

Bitset* IntToBitset(int num) {
    size_t blocks = sizeof(num);
    bit_block* bits = malloc(blocks * sizeof(bit_block));
    if (!bits) return NULL;

    bits[0] = num & 0x000000ff;
    bits[1] = (num & 0x0000ff00) >> 8;
    bits[2] = (num & 0x00ff0000) >> 16;
    bits[3] = (num & 0xff000000) >> 24;
    Bitset* bitset = malloc(sizeof(Bitset));
    bitset->bits = bits;
    bitset->blocks = blocks;
    bitset->len = blocks * BITS_IN_BYTE;
    return bitset;
}

void FreeBitset(Bitset* bitset) {
    free(bitset->bits);
    free(bitset);
}

bool BitsetGetN(Bitset* bitset, size_t n) {
    if (n >= bitset->len) return 0;

    div_t n_div = div(n, BITS_IN_BLOCK);
    return (bitset->bits[n_div.quot] >> n_div.rem) & 1;
}

void BitsetSetN(Bitset* bitset, size_t n, bool bit) {
    if (n >= bitset->len) return;

    div_t n_div = div(n, BITS_IN_BLOCK);

    if (bit)
        bitset->bits[n_div.quot] |= (1 << n_div.rem);
    else
        bitset->bits[n_div.quot] &= ~(1 << n_div.rem);
}

char* StrBitset(Bitset* bitset) {
    size_t p = 0;
    char* str = malloc(bitset->len * sizeof(char) + 1);
    bit_block ptr;
    bit_block max_bit = (bit_block)(1 << (BITS_IN_BLOCK - 1));

    for (size_t i = 0; i < bitset->blocks; i++) {
        ptr = 1;
        while (p < bitset->len) {
            str[p++] = '0' + ((bitset->bits[i] & ptr) > 0 ? 1 : 0);
            if (ptr == max_bit) break;
            ptr <<= 1;
        }
    }

    str[p] = '\0';
    return str;
}

Bitset* BinSum(Bitset* num1, Bitset* num2) {
    if (num1->len != num2->len) return NULL;

    Bitset* result = NewBitset(num1->len + 1);
    if (!result) return NULL;

    int carry = 0;
    size_t i;
    for (i = 0; i < num1->len; i++) {
        carry += BitsetGetN(num1, i) + BitsetGetN(num2, i);
        if (carry & 1) {
            carry = 0;
            BitsetSetN(result, i, 1);
        }
        if (carry > 1) carry = 1;
    }

    BitsetSetN(result, i, carry);
    return result;
}
