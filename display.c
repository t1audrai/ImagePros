#include "display.h"
#include <string.h>
#include <sys/ioctl.h>


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


void displayPictureBlack(uint8_t * inFrame,int width, int height)
{	
	int i = width*height-1;
	for (int h = height-1; h >= 0; h--) {
					for (int w = width-1; w >= 0; w--) {
										
						int B = inFrame[i];
						SET_PIXEL(w,h,RGB(B,B,B));
						i--;
				}
	}

}









