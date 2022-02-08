#ifndef _MAGIC_H_
#define _MAGIC_H_

#include <bits.h>

enum { DDIAG, DRANK, DFILE };

typedef struct { board_t mask, *attacks;
               } magic_t;

extern magic_t magics[3][64];
extern board_t attacks[0x15600];

void init_magics();

static board_t moves(int sq, board_t occ) {
  return magics[DDIAG][sq].attacks[pext(occ, magics[DDIAG][sq].mask)]
       | magics[DRANK][sq].attacks[pext(occ, magics[DRANK][sq].mask)]
       | magics[DFILE][sq].attacks[pext(occ, magics[DFILE][sq].mask)];
}

#endif /*_MAGIC_H_*/
