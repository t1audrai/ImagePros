#include <stdint.h>				// uint_8		
#include "decode.h"
#include "CVtool.h"
#include "myPrint.h"




#define WIDTH 640;
#define HEIGHT 480;
#define F_POS(x, y) (x+y*WIDTH);

void borderdetector2(uint8_t* input, int width, int height, uint8_t* output, int threshold ) {
		
		unsigned int i,j,k=0;
		int pos;
		int temp_h = 0;
		int temp_v = 0;
		int norm =0;
		int prewitt_H[9] = { -1, -1, -1, 0, 0, 0, 1, 1, 1};		
		int prewitt_V[9] = { -1, 0, 1, -1, 0, 1, -1, 0, 1};
		int sub[9];
	
	
		for(i=1;i<height-1;++i){
			for(j=1;j< width-1;++j){
				
					
					
						
						pos = (i+1)*(width-1)+(j);
						sub[6] =  input[pos-1];
						sub[7] =  input[pos];					 
						sub[8] =  input[pos+1];				 
											 		
						pos -= (width-1);
						sub[3] =  input[pos-1];
						sub[4] =  input[pos];					 
						sub[5] =  input[pos+1];	
						
						pos -= (width-1);					 		
						sub[0] =  input[pos-1];
						sub[1] =  input[pos];					 
						sub[2] =  input[pos+1];				 
											 
					
						pos += (width-1);
						 
											 
						
						temp_h =0;
						temp_v =0;
						int l = 8;
						for(l=8; l>=0; l--){
							temp_h += (sub[l]*prewitt_H[l]);
							temp_v += (sub[l]*prewitt_V[l]);
						}
						
						
						norm=temp_h*temp_h +temp_v*temp_v;
									
						
						output[pos] =(norm >= threshold)? 254:0;
					
						k++;
					}
						
		}
		
	
}



