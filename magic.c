#include <bits.h>
#include <kogge.h>
#include <magic.h>

magic_t magics[3][64];
board_t attacks[0x15600];

void init_magics() {
  int idx = 0;

  for (int type = 0; type < 3; type++) {
    board_t (*slider)(int, board_t, bool) =
      (type == DDIAG) ? diag_sliders :
      (type == DRANK) ? rank_sliders :
      (type == DFILE) ? file_sliders : 0;

    for (int sq = 0; sq < 64; sq++) {
      board_t mask = slider(sq, 0, false);
      board_t occ = 0;

      magics[type][sq].mask = mask;
      magics[type][sq].attacks = attacks + idx;

      do {
        attacks[idx++] = slider(sq, occ, true) | bit(sq);
        occ = (occ - mask) & mask;
      } while (occ);
    }
  }
}
