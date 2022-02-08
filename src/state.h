#ifndef _STATE_H_
#define _STATE_H_

#include <magic.h>

typedef struct { board_t black, white;
               } state_t;

static state_t start_state() {
  return (state_t) { 0x1008000000, 0x810000000 };
}

static board_t get_moves(state_t state) {
  board_t occ  = state.black | state.white;
  board_t mask = 0;

  for (bits(sq, state.black)) {
    mask |= moves(sq, ~state.white);
  }

  return mask &~ occ;
}

static state_t make_move(int sq, state_t state) {
  board_t opp  = moves(sq, ~state.white) & state.black;
  board_t flip = moves(sq, opp);

  return (state_t) { state.white &~ flip, state.black | flip };
}

static state_t pass_move(state_t state) {
  return (state_t) { state.white, state.black };
}

#endif /*_STATE_H_*/
