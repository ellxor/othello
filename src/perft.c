#include <bits.h>
#include <perft.h>
#include <pthread.h>

long perft(state_t state, int depth) {
  board_t mask = get_moves(state);

  if (depth == 1) {
    return mask ? pop(mask) : 1;
  }

  if (!mask) {
    return perft(pass_move(state), depth - 1);
  }

  long total = 0;

  for (bits(sq, mask)) {
    total += perft(make_move(sq, state), depth  - 1);
  }

  return total;
}

long multi_start_perft(int depth);

long start_perft(int depth) {
  state_t state = start_state();

  if (depth == 0) return 1;
  if (depth == 1) return perft(state, 1);

  if (depth < 11) {
    board_t mask = get_moves(state);
    state = make_move(ctz(mask), state);
    return 4 * perft(state, depth - 1);
  }

  return multi_start_perft(depth);
}

typedef struct { state_t state; int depth; long nodes;
               } perft_t;

void *perft_wrapper(void *arg) {
  perft_t *data = arg;
  data->nodes = perft(data->state, data->depth);
  return NULL;
}

long multi_start_perft(int depth) {
  state_t state = start_state();
  board_t mask  = get_moves(state);

  state = make_move(ctz(mask), state);
  mask  = get_moves(state);

  pthread_t threads[3];
  perft_t data[3];
  long total = 0;
  int i = 0;

  for (bits(sq, mask)) {
    data[i] = (perft_t) { make_move(sq, state), depth - 2, 0 };
    pthread_create(&threads[i], NULL, perft_wrapper, &data[i]);
    i += 1;
  }

  while (i --> 0) {
    pthread_join(threads[i], NULL);
    total += data[i].nodes;
  }

  return 4 * total;
}
