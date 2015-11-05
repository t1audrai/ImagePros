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

void displayPictureRGB(const uint8_t * inFrame,int width, int height)
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


void displayPictureBlack(const uint8_t * inFrame,int width, int height, int X_offset, int Y_offset)
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







void displayCircle(const uint8_t * inFrame,const uint8_t * backFrame,  int width, int height, int X_offset, int Y_offset)
{	
	int i =0;       
	for (int h = 0; h < height; h++) {
				for (int w = 0; w < width; w++) {
							
                                    if( (shape[inFrame[i]].isCircle == 1 && shape[inFrame[i]].tooSmall == 0) ||  inFrame[i] == 255){ //est un cercle
											SET_PIXEL(w+X_offset,h+Y_offset,RGB(0,255,0));
											SET_PIXEL(shape[inFrame[i]].center.x + X_offset,shape[inFrame[i]].center.y +Y_offset,RGB(0,255,0));
					                }
                                
                                    
                                    else if(shape[inFrame[i]].isCircle == 0  && inFrame[i] !=0 && shape[inFrame[i]].tooSmall == 0) {
                                            SET_PIXEL(w+X_offset,h+Y_offset,RGB(255,0,0));
                                    }
                                    else{
											SET_PIXEL(w+X_offset,h+Y_offset,RGB(backFrame[i],backFrame[i],backFrame[i]));  
                                    }
                                    i++;
                                    
                                    
                                    
                                }   
                                
	}
	
	
	 /*for(int j = 1; j <12; j++){
        
			//log_wtf("","radius%d :  x : %d , y : %d",j,shape[j].max.x -shape[j].min.x ,shape[j].max.y - shape[j].min.y );
		//log_wtf("","min%d :  x : %d , y : %d",j,shape[j].min.x ,shape[j].min.y );
		//log_wtf("","max%d :  x : %d , y : %d",j,shape[j].max.x ,shape[j].max.y );
			SET_PIXEL(shape[j].center.x + X_offset,shape[j].center.y +Y_offset,RGB(255,255,255));
			//SET_PIXEL(shape[j].max.x + X_offset,shape[j].max.y +Y_offset,RGB(255,255,255));
		//SET_PIXEL(shape[j].min.x + X_offset,shape[j].min.y +Y_offset,RGB(255,255,255));
			
			//SET_PIXEL(shape[j].min.x +X_offset,shape[j].min.y +Y_offset,RGB(0,0,0));
   
       }*/
      
	
	
	
	

}



void displayPictureFC(const uint8_t * inFrame,int width, int height, int X_offset, int Y_offset)
{	
	int i = width*height-1;
	for (int h = height-1; h >= 0; h--) {
					for (int w = width-1; w >= 0; w--) {
										
						int B = inFrame[i];
						SET_PIXEL(w+X_offset,h+Y_offset,RGB(Blue(B),Green(B),Red(B)));
						i--;
				}
	}

}






