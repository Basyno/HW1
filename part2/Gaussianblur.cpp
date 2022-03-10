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
    int buffersize[3][258]={{ }};

void Gaussianblur::do_gblur() {
  while (true) {
  	
    int total = 0;
    int x_pixel = 0;
    int y_pixel = 0;
    x_pixel = input_image_pixel_x.read();
    y_pixel = input_image_pixel_y.read();
    
    if(x_pixel == -1 && y_pixel == -1){		
    	for(int m=0;m<3;m++){
    		for(int n=0;n<258;n++){
    			buffersize[m][n]=0;
			}
		}
	}
    
	if(x_pixel == -1){
    	for (unsigned int j=0;j<1;j++){
    		for (unsigned int k = 0; k < 258; k++) {	
			buffersize[j][k] = buffersize[j+1][k];
    		buffersize[j+1][k] = buffersize[j+2][k];

        	} 	
    	}
    }
    
    buffersize[2][x_pixel+1] = (i_r.read() + i_g.read() + i_b.read()) / 3 ;
	
    if(x_pixel >= 1 && y_pixel >= 1){
      for (unsigned int v = 0; v < MASK_Y; ++v) {
        for (unsigned int u = 0; u < MASK_X; ++u) {
        	for(unsigned int w = 0; w < MASK_N; ++w)
          total += buffersize[v][u+x_pixel-1] * mask[w][v][u];
	       
        } 
	  }   

      o_result.write(total);

      wait(1); //emulate module delay
    }

  }
}

