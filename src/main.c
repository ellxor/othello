#include <stdio.h>
#include <time.h>

#include <magic.h>
#include <state.h>
#include <perft.h>

double get_time() {
  struct timespec ts;
  timespec_get(&ts, TIME_UTC);

  return (double)ts.tv_sec + (double)ts.tv_nsec / 1e9;
}

int main() {
  clock_t t1 = clock();
  init_magics();
  clock_t t2 = clock();

  size_t bytes = sizeof attacks;
  clock_t time = t2 - t1;

  printf("Table size = %ld bytes\n", bytes);
  printf("Table init = %ld clocks\n", time);

  double seconds = 0;
  long total = 0;

  for (int depth = 1; depth <= 14; depth++) {
    double t1 = get_time();
    long nodes = start_perft(depth);
    double t2 = get_time();

    printf("%2d: %12ld\n", depth, nodes);

    seconds += t2 - t1;
    total += nodes;
  }

  printf("(%.2f Gnps)\n", total / seconds / 1e9);
}
