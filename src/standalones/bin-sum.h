#ifndef BIN_SUM_H
#define BIN_SUM_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "utils/utils.h"

typedef struct {
    bit_block* bits;
    size_t len;
    size_t blocks;
} Bitset;

void BitsetClear(Bitset* bitset);

Bitset* NewBitset(size_t len);

void FreeBitset(Bitset* bitset);

bool BitsetGetN(Bitset* bitset, size_t n);

void BitsetSetN(Bitset* bitset, size_t n, bool bit);

Bitset* IntToBitset(int num);

char* StrBitset(Bitset* bitset);

Bitset* BinSum(Bitset* num1, Bitset* num2);

#endif /* ifndef BIN_SUM_H */
