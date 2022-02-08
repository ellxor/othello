#include <stdio.h>
#include <time.h>

#include <magic.h>
#include <state.h>
#include <perft.h>

int main() {
  clock_t t1 = clock();
  init_magics();
  clock_t t2 = clock();

  size_t bytes = sizeof attacks;
  clock_t time = t2 - t1;

  printf("Table size = %ld bytes\n", bytes);
  printf("Table init = %ld clocks\n", time);

  clock_t delta = 0;
  long total = 0;

  for (int depth = 1; depth <= 12; depth++) {
    clock_t t1 = clock();
    int nodes = start_perft(depth);
    clock_t t2 = clock();

    printf("%2d: %10d\n", depth, nodes);

    delta += t2 - t1;
    total += nodes;
  }

  double seconds = (double)delta / CLOCKS_PER_SEC;
  printf("(%.2f Gnps)\n", total / seconds / 1e9);
}