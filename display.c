#include "display.h"
#include "CVtool.h"
#include <string.h>
#include <sys/ioctl.h>


int myColor[12] = {0x000000 ,0xFF0012, 0x00FF40, 0x0010FF, 0x7800FF,0xFFFF00, 0x007878, 0xFFFFFF, 0x00FFFF, 0xFF00FF, 0x502465, 0xFF8952 };

void rect_fill(int x,int y, int w, int h, unsigned short color)
{
	int i, j;
	for (i=0;i<w;i++) {
		for (j=0;j<h;j++) {
			SET_PIXEL(x+i,y+j,color);
		}
	}
}

void displayPictureRGB(uint8_t * inFrame,int width, int height)
{	
	int i = 0;
	for (int h = 0; h < height; h++) {
				for (int w = 0; w < width; w++) {
					
						int R = inFrame[i];
						int G = inFrame[i+1];
						int B = inFrame[i+2];
						
						SET_PIXEL(w,h,RGB(R,G,B));
						i+=3;
				}
	}

}


void displayPictureBlack(uint8_t * inFrame,int width, int height, int X_offset, int Y_offset)
{	
	int i = width*height-1;
	for (int h = height-1; h >= 0; h--) {
					for (int w = width-1; w >= 0; w--) {
										
						int B = inFrame[i];
						SET_PIXEL(w+X_offset,h+Y_offset,RGB(B,B,B));
						i--;
				}
	}

}



void displayPictureFC(uint8_t * inFrame,int width, int height, int X_offset, int Y_offset)
{	
	int i =0;
                
	for (int h = 0; h < height; h++) {
				for (int w = 0; w < width; w++) {
                                                SET_PIXEL(w+X_offset,h+Y_offset,RGB(R(inFrame[i]),G(inFrame[i]),B(inFrame[i])));
						i++;
				}
	}

}


void displayCircle(uint8_t * inFrame,int width, int height, int X_offset, int Y_offset)
{	
	int i =0;
        int j = 0;
        
       
        
	for (int h = 0; h < height; h++) {
				for (int w = 0; w < width; w++) {
							
                                    if( shape[inFrame[i]].isCircle == 1 ){ //est un cercle
					SET_PIXEL(w+X_offset,h+Y_offset,RGB(R(2),G(2),B(2)));
				    }
                                    else if(shape[inFrame[i]].isCircle == 0  && inFrame[i] !=0) {
                                        SET_PIXEL(w+X_offset,h+Y_offset,RGB(R(1),G(1),B(1)));
                                    }
                                    else{
                                        SET_PIXEL(w+X_offset,h+Y_offset,RGB(R(0),G(0),B(0)));
                                        
                                    }
                                    i++;
                                }   
                                
	}

}











