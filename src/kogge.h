#ifndef _KOGGE_H_
#define _KOGGE_H_

#include <bits.h>
#include <stdbool.h>

enum { N = 8, E = 1, S = -N, W = -E,
       NE = N+E, NW = N+W, SE = S+E, SW = S+W };

static board_t wrap(int shift) {
  return (shift ==  N) ? 0xffffffffffffff00 :
         (shift ==  E) ? 0xfefefefefefefefe :
         (shift ==  S) ? 0x00ffffffffffffff :
         (shift ==  W) ? 0x7f7f7f7f7f7f7f7f :
         (shift == NE) ? 0xfefefefefefefe00 :
         (shift == NW) ? 0x7f7f7f7f7f7f7f00 :
         (shift == SE) ? 0x00fefefefefefefe :
         (shift == SW) ? 0x007f7f7f7f7f7f7f : 0;
}

static board_t sliders(int sq, board_t occ, int shift, bool opp) {
  board_t gen = bit(sq);
  board_t pro = ~occ & wrap(shift);

  gen |= pro & rotl(gen, shift);
  pro &=       rotl(pro, shift);
  gen |= pro & rotl(gen, shift * 2);
  pro &=       rotl(pro, shift * 2);
  gen |= pro & rotl(gen, shift * 4);

  gen = rotl(gen, shift) & wrap(shift);

  if (opp && (pop(gen) == 1 || !(gen & occ))) {
    return 0;
  }
  return gen;
}

static board_t diag_sliders(int sq, board_t occ, bool opp) {
  return sliders(sq, occ, NE, opp)
       | sliders(sq, occ, NW, opp)
       | sliders(sq, occ, SE, opp)
       | sliders(sq, occ, SW, opp);
}

static board_t rank_sliders(int sq, board_t occ, bool opp) {
  return sliders(sq, occ, E, opp)
       | sliders(sq, occ, W, opp);
}

static board_t file_sliders(int sq, board_t occ, bool opp) {
  return sliders(sq, occ, N, opp)
       | sliders(sq, occ, S, opp);
}

#endif /*_KOGGE_H_*/
