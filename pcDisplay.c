
#include "pcDisplay.h"
#include <string.h>
#include <sys/ioctl.h>



int color[7] = {0x000000 ,0xFF0012, 0x00FF40, 0x0010FF, 0x7800FF,0xFFFF00, 0x007878 };

void pcDisplayPictureRGB(uint8_t * inFrame,int width, int height, int X_offset, int Y_offset)
{	
	int i = 0;
	for (int h = 0; h < height; h++) {
				for (int w = 0; w < width; w++) {
					
						outScreen[i] = inFrame[i];
						outScreen[i+1] = inFrame[i+1];
						outScreen[i+2]= inFrame[i+2];
						
                                         	i+=3;
				}
	}

}


void pcDisplayPictureBlack(uint8_t * inFrame,int width, int height, int X_offset, int Y_offset)
{	
    
        int i =0;
        int j = 0;
	for (int h = 0; h < height; h++) {
				for (int w = 0; w < width; w++) {
										
						outScreen[j++] = inFrame[i];
						outScreen[j++] = inFrame[i];
                                                outScreen[j++] = inFrame[i];
						i++;
				}
	}

}


void pcDisplayPictureFC(uint8_t * inFrame,int width, int height, int X_offset, int Y_offset)
{	
	int i =0;
        int j = 0;
        
	for (int h = 0; h < height; h++) {
				for (int w = 0; w < width; w++) {
										
						outScreen[j++] = R(inFrame[i]); //b
						outScreen[j++] = G(inFrame[i]); //g
                                                outScreen[j++] = B(inFrame[i]); //r
						i++;
				}
	}

}










