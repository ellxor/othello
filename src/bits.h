#ifndef _BITS_H_
#define _BITS_H_

#include <stdint.h>
#include <x86intrin.h>

typedef uint64_t board_t;

#define bit(sq)         (1ull << (sq))
#define ctz(mask)       (__builtin_ctzll(mask))
#define pext(a, mask)   (_pext_u64(a, mask))
#define pop(mask)       (__builtin_popcountll(mask))
#define rotl(mask, s)   (_lrotl(mask, s))

#define bits(sq, mask)  int sq; mask && (sq = ctz(mask)), mask; \
                        mask &= mask - 1

#endif /*_BITS_H_*/
