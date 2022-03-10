#include <cmath>

#include "Gaussianblur.h"

Gaussianblur::Gaussianblur(sc_module_name n) : sc_module(n) {
  SC_THREAD(do_gblur);
  sensitive << i_clk.pos();
  dont_initialize();
  reset_signal_is(i_rst, false);
}

// sobel mask
const double mask[MASK_N][MASK_X][MASK_Y] = {{{0.0625, 0.125, 0.0625}, {0.125, 0.25, 0.125}, {0.0625, 0.125, 0.0625}}
                                             
                                         };
                                         
void Gaussianblur::do_gblur() {
  while (true) {
    for (unsigned int i = 0; i < MASK_N; ++i) {
      val[i] = 0;
    }
    for (unsigned int v = 0; v < MASK_Y; ++v) {
      for (unsigned int u = 0; u < MASK_X; ++u) {
        unsigned char grey = (i_r.read() + i_g.read() + i_b.read()) / 3;
        for (unsigned int i = 0; i != MASK_N; ++i) {
          val[i] += grey * mask[i][u][v];
        }
      }
    }
    double total = 0;
    for (unsigned int i = 0; i != MASK_N; ++i) {
      total += val[i];
    }
    int result = (int)(total);
    o_result.write(result);
    wait(10); //emulate module delay
  }
}
