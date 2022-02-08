#include <stdio.h>
#include <time.h>
#include <magic.h>

typedef struct { board_t black, white;
               } state_t;

board_t get_moves(state_t s) {
  board_t mask = 0;
  board_t occ = s.black | s.white;

  for (bits(sq, s.black)) {
    mask |= moves(sq, ~s.white);
  }

  return mask &~ occ;
}

state_t make_move(int sq, state_t s) {
  board_t opp  = moves(sq, ~s.white) & s.black;
  board_t flip = moves(sq, opp);

  return (state_t) { s.white &~ flip, s.black | flip };
}

state_t pass_move(state_t s) {
  return (state_t) { s.white, s.black };
}

int perft(state_t state, int depth) {
  board_t mask = get_moves(state);

  if (depth == 1) {
    return pop(mask) ?: 1;
  }

  if (!mask) {
    return perft(pass_move(state), depth - 1);
  }

  int total = 0;

  for (bits(sq, mask)) {
    total += perft(make_move(sq, state), depth - 1);
  }

  return total;
}

int rotperft(state_t state, int depth) {
  if (depth == 1) {
    return perft(state, 1);
  }

  board_t mask = get_moves(state);
  state = make_move(ctz(mask), state);
  return 4 * perft(state, depth - 1);
}

int main() {
  clock_t t1 = clock();
  init_magics();
  clock_t t2 = clock();

  size_t bytes = sizeof attacks;
  clock_t time = t2 - t1;

  printf("Table size = %ld bytes\n", bytes);
  printf("Table init = %ld clocks\n", time);

  state_t init = { bit(27) | bit(36), bit(28) | bit(35) };

  clock_t delta = 0;
  long total = 0;

  for (int depth = 1; depth <= 12; depth++) {
    clock_t t1 = clock();
    int nodes = rotperft(init, depth);
    clock_t t2 = clock();

    printf("%2d: %10d\n", depth, nodes);

    delta += t2 - t1;
    total += nodes;
  }

  double seconds = (double)delta / CLOCKS_PER_SEC;
  printf("(%.2f Gnps)\n", total / seconds / 1e9);
}