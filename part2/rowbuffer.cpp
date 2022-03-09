#include <cmath>

#include "rowbuffer.h"

Gaussianblur::Gaussianblur(sc_module_name n) : sc_module(n) {
//SC_THREAD(do_gblur);
SC_THREAD(rowbuffer);
  sensitive << i_clk.pos();
  dont_initialize();
  reset_signal_is(i_rst, false);
}

// sobel mask
const double mask[MASK_N][MASK_X][MASK_Y] = {{{0.0625, 0.125, 0.0625}, {0.125, 0.25, 0.125}, {0.0625, 0.125, 0.0625}}
                                             
                                         };

int rowbuffersize[3][256];
int  count=0,m=0,n=0;


                            
void Gaussianblur::rowbuffer() {
    
	
	for(unsigned int m=0 ; m<3 ; ++m)
	{
		for(unsigned int n=0 ; n<256 ; ++n)
		{
			rowbuffersize[m][n]=0;
		}
	} 
    
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
    count = count + 1;
    if (count==256)
    {
    	m =m+1;
    	count=0;
	}
	for(m=0;m<3;m++){
   	rowbuffersize[m][count-1] =total;
}
    int result = (int)(total);
    o_result.write(result);
    wait(9); //emulate module delay
  }
}
