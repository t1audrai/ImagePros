#include <stdint.h>				// uint_8		
#include "decode.h"
#include "CVtool.h"
#include "myPrint.h"


#define WIDTH 640;
#define HEIGHT 480;
#define F_POS(x,y) (x+y*WIDTH);
int BACKGROUND = 0;
int OBJECT = 255;





int imageMean(uint8_t* input, int width, int height){
    
        unsigned int size = width*height;
        unsigned int i,j;
	double tmp_mean=0;
   
    	for(i=height-2;i>=1;i--){
			for(j=width-2;j>=1;j--){
					tmp_mean += input[(i+1)*(width-1)+(j)];
			}
		}
		
        return tmp_mean/size;
    
}



void thresholding(uint8_t* input, int width, int height, uint8_t* output, int coefDispersion ){
                
                unsigned int size = width*height;
		unsigned int k=size-1;		
		int threshold,highest=0,highestPos=0;
             
                
                
                unsigned int histo[8] = {0,0,0,0,0,0,0,0};               
                for (int h = height-2; h >= 1; h--) {
					for (int w = width-2; w >= 1; w--) {	
							histo[input[k--] >> 5] ++; // division par 16
                                                        
                                                        
			}
		}
                 
                
                for(int i=7; i>=0; i--){
                    log_i("","histo[%d] :%d",i,histo[i]);
                    if (histo[i] > highest){
                        highest = histo[i];
                        highestPos = i;
                    }
                   
                }
                
               
                log_i("highestPos","highestPos :%d\n",highestPos);
       
                if( (highestPos-4) < 0){
                    
                    //black background
                    threshold = (highestPos << 5) +32;                  
                    k=size-1;
                    for (int h = height-2; h >= 1; h--) {
			for (int w = width-2; w >= 1; w--) {			
                            output[k] = (input[k] < threshold )? BACKGROUND:OBJECT;
                            k--;			
                        }
                    }
                    
                }
                else{
                    
                     //white background
                    threshold = highestPos << 5; 
                    log_i("white background","threshold :%d\n",threshold);
                    k=size-1;
                    for (int h = height-2; h >= 1; h--) {
			for (int w = width-2; w >= 1; w--) {			
                            output[k] = (input[k] > threshold )? BACKGROUND:OBJECT;
                            k--;			
                        }
                    }
                }
                    
                
           
          
           
                 
             
    
}


void erosion3x3(uint8_t* input, int width, int height, uint8_t* output){
    
                int erosion[9] = {OBJECT, OBJECT, OBJECT, OBJECT, OBJECT, OBJECT, OBJECT, OBJECT, OBJECT};
                int sub[9];
                unsigned int i,j,pos;
		for(i=height-2;i>=1;i--){
				for(j=width-2;j>=1;j--){
					
					
										
						pos = (i+1)*(width-1)+(j);
						sub[6] =  input[pos-1] && erosion[6];
						sub[7] =  input[pos]   && erosion[7];					 
						sub[8] =  input[pos+1] && erosion[8];				 
											 		
						pos -= (width-1);
						sub[3] =  input[pos-1] && erosion[3];			 
						sub[5] =  input[pos+1] && erosion[5];	
						
						pos -= (width-1);					 		
						sub[0] =  input[pos-1] && erosion[0];
						sub[1] =  input[pos]   && erosion[1];					 
						sub[2] =  input[pos+1] && erosion[2];	
						
						pos += (width-1);
					
					if( sub[1] && sub[2] && sub[3] && sub[5] && sub[6] && sub[7] && sub[8]){
					
								output[pos] = OBJECT;  
					}
					else{
								output[pos] = BACKGROUND; 
					}
					
	
			}
		}
    
}

void dilation3x3(uint8_t* input, int width, int height, uint8_t* output){

                int dilatation[9] = {OBJECT, OBJECT, OBJECT, OBJECT, OBJECT, OBJECT, OBJECT, OBJECT, OBJECT};	
                unsigned int i,j,pos;
		int sub[9];
		for(i=height-2;i>=1;i--){
				for(j=width-2;j>=1;j--){
					
					
										
						pos = (i+1)*(width-1)+(j);
						sub[6] =  input[pos-1] && dilatation[6];
						sub[7] =  input[pos]   && dilatation[7];					 
						sub[8] =  input[pos+1] && dilatation[8];				 
											 		
						pos -= (width-1);
						sub[3] =  input[pos-1] && dilatation[3];			 
						sub[5] =  input[pos+1] && dilatation[5];	
						
						pos -= (width-1);					 		
						sub[0] =  input[pos-1] && dilatation[0];
						sub[1] =  input[pos]   && dilatation[1];					 
						sub[2] =  input[pos+1] && dilatation[2];	
						
						pos += (width-1);
					
					if( sub[1] || sub[2] || sub[3] || sub[5] || sub[6] || sub[7] ||sub[8]){
					
								output[pos] = OBJECT;
								
					}
					else{
								output[pos] = BACKGROUND; 
					}
					
	
			}
		}
    
}


void shapeDetector(uint8_t* input, int width, int height, uint8_t* output, int R ) {
		
                uint8_t tmp[614400];
                uint8_t tmp2[614400];
    
                thresholding(input, width,height, tmp, 100);
		borderDetector(tmp,width,height,tmp2,28);
                dilation3x3(tmp2,width,height,tmp);
                erosion3x3(tmp,width,height,output);
                
                
                /*
		
		
		
		
		//segmentation
		int nbElement = 0;	

		for(i=height-2;i>=1;i--){
				for(j=width-2;j>=1;j--){
					
				
						pos = (i)*(width-1)+(j);
						
						if(tmp2[pos] == 255){
								if(tmp2[pos+1] == 0){
										if(tmp2[pos-(width-1)] == 0){
												nbElement ++;
												output[pos] = nbElement +1;
												
										}
										else{
											output[pos] = output[pos-(width-1)];
										}
					
								}
								else{
								
									output[pos] = output[pos+1];
								
								} 

	
						}
						
						else{
							output[pos] = 0;
						}
				}

		
		
		
		}*/
	
}


void borderDetector(uint8_t* input, int width, int height, uint8_t* output, int R ) {
		
                int size = width*height;
		unsigned int i,j,k=size-1;
		int pos;
		int temp_h=0,temp_v = 0;
		int norm = 0;
		
		double tmp_mean=0;
		uint8_t mean =0;
		
		int prewitt_H[9] = { -1, -1, -1, 0, 0, 0, 1, 1, 1};		
		int prewitt_V[9] = { -1, 0, 1, -1, 0, 1, -1, 0, 1};
		
		int sobel_H[9] = { -1, -2, -1, 0, 0, 0, 1, 2, 1};		
		int sobel_V[9] = { -1, 0, 1, -2, 0, 2, -1, 0, 1};
	
		int sub[9];
		
	
		int threshold = imageMean(input, width, height) * R;
		
		for(i=height-2;i>=1;i--){
			for(j=width-2;j>=1;j--){
				
					
					
 
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
						
						for(int l=8; l>=0; l--){
							//temp_h += (sub[l]*prewitt_H[l]);
							//temp_v += (sub[l]*prewitt_V[l]);
							
							temp_h += (sub[l]*sobel_H[l]);
							temp_v += (sub[l]*sobel_V[l]);
						}
						
						
						norm=temp_h*temp_h + temp_v*temp_v;
									
						
						output[pos] =(norm >= threshold)? OBJECT:BACKGROUND;
					
						k--;
					}
						
		}
		
	
}
