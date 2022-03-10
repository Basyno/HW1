#include <iostream>
#include <string>
using namespace std;

// Wall Clock Time Measurement
#include <sys/time.h>

#include "Gaussianblur.h"
#include "Testbench.h"

// TIMEVAL STRUCT IS Defined ctime
// use start_time and end_time variables to capture
// start of simulation and end of simulation
struct timeval start_time, end_time;

// int main(int argc, char *argv[])
int sc_main(int argc, char **argv) {
  if ((argc < 3) || (argc > 4)) {
    cout << "No arguments for the executable : " << argv[0] << endl;
    cout << "Usage : >" << argv[0] << " in_image_file_name out_image_file_name"
         << endl;
    return 0;
  }

  //Create modules and signals
  Testbench tb("tb");
  Gaussianblur gblur("gblur");
  sc_clock clk("clk", CLOCK_PERIOD, SC_NS);
  sc_signal<bool> rst("rst");


  //Create FIFO channels
  sc_fifo<unsigned char> r;
  sc_fifo<unsigned char> g;
  sc_fifo<unsigned char> b;
  sc_fifo<int> x;
  sc_fifo<int> y;
  sc_fifo<int> result;

  //Connect FIFO channels with modules
  tb.i_clk(clk);
  tb.o_rst(rst);
  gblur.i_clk(clk);
  gblur.i_rst(rst);
  tb.o_r(r);
  tb.o_g(g);
  tb.o_b(b);
  tb.output_image_pixel_x(x);
  tb.output_image_pixel_y(y);
  tb.i_result(result);
  gblur.i_r(r);
  gblur.i_g(g);
  gblur.i_b(b);
  gblur.input_image_pixel_x(x);
  gblur.input_image_pixel_y(y);
  gblur.o_result(result);

  tb.read_bmp(argv[1]);
  sc_start();
  std::cout << "Simulated time == " << sc_core::sc_time_stamp() << std::endl;
  tb.write_bmp(argv[2]);

  return 0;
}
