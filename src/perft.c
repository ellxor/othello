#include <bits.h>
#include <perft.h>

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
    total += perft(make_move(sq, state), depth  - 1);
  }

  return total;
}

int start_perft(int depth) {
  state_t state = start_state();

  if (depth == 0) return 1;
  if (depth == 1) return perft(state, 1);

  board_t mask = get_moves(state);
  state = make_move(ctz(mask), state);
  return 4 * perft(state, depth - 1);
}
