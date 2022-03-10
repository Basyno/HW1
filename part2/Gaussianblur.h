#ifndef SOBEL_FILTER_H_
#define SOBEL_FILTER_H_
#include <systemc>
using namespace sc_core;

#include "filter_def.h"

class Gaussianblur : public sc_module {
public:
  sc_in_clk i_clk;
  sc_in<bool> i_rst;
  sc_fifo_in<unsigned char> i_r;
  sc_fifo_in<unsigned char> i_g;
  sc_fifo_in<unsigned char> i_b;
  sc_fifo_in<int> input_image_pixel_x;
  sc_fifo_in<int> input_image_pixel_y;
  sc_fifo_out<int> o_result;
  
  SC_HAS_PROCESS(Gaussianblur);
  Gaussianblur(sc_module_name n);
  ~Gaussianblur() = default;

private:
	
  void do_gblur();
  
};
#endif
