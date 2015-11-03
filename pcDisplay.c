#include "CVtool.h"
#include "pcDisplay.h"
#include <string.h>
#include <sys/ioctl.h>



int color[12] = {0x000000 ,0xFF0012, 0x00FF40, 0x0010FF, 0x7800FF,0xFFFF00, 0x007878, 0xFFFFFF, 0x00FFFF, 0xFF00FF, 0x502465, 0xFF8952 };


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
								
                                    
                                    
                                            if(shape[inFrame[i]].tooSmall == 0 ){ //est un cercle
                                                    outScreen[j++] = R(inFrame[i]); //R
                                                    outScreen[j++] = G(inFrame[i]); //G
                                                    outScreen[j++] = B(inFrame[i]); //B
                                                    i++;

                                           }
                                            else{
                                                    outScreen[j++] = R(0); //R
                                                    outScreen[j++] = G(0); //G
                                                    outScreen[j++] = B(0); //B
                                                    i++;
                                                
                                            }
   	
				}
	}

}


void pcDisplayCircle(uint8_t * inFrame,int width, int height, int X_offset, int Y_offset)
{	
	int i =0;
        int j = 0;
        
       
        
	for (int h = 0; h < height; h++) {
				for (int w = 0; w < width; w++) {
							
                                    
                                    
                                   // if(shape[inFrame[i]].tooSmall == 0){
                                    
                                                    if( shape[inFrame[i]].isCircle == 1 && shape[inFrame[i]].tooSmall == 0){ //est un cercle
                                                                outScreen[j++] = R(2); //R
                                                                outScreen[j++] = G(2); //G
                                                                outScreen[j++] = B(2); //B

                                                    }


                                                    else if(shape[inFrame[i]].isCircle == 0  && inFrame[i] !=0 && shape[inFrame[i]].tooSmall == 0) {
                                                                outScreen[j++] = R(1); //R
                                                                outScreen[j++] = G(1); //G
                                                                outScreen[j++] = B(1); //B
                                                    }                
                                  // }
                                    else{
                                                outScreen[j++] = R(0); //R
						outScreen[j++] = G(0); //G
                                                outScreen[j++] = B(0); //B
                                        
                                    }
                                    i++;
                                }   
                                
	}

}





