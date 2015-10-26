#include <stdint.h>				// uint_8		
#include "decode.h"
#include "CVtool.h"
#include "myPrint.h"
#include "pcDisplay.h"


#define WIDTH 640;
#define HEIGHT 480;
#define F_POS(x,y) (x+y*WIDTH);
int BACKGROUND = 0;
int OBJECT = 255;


 int imageMean(uint8_t* input, int width, int height){
    
     
        unsigned int size = width*height;
        unsigned int k=size-1;	
        double tmp_mean=0;
   
    
          for (int h = height-1; h >= 0; h--) {
		for (int w = width-1; w >= 0; w--) {	
			tmp_mean += input[k--];
                }
	  }
 	
        return tmp_mean/size;
    
}



void thresholding(uint8_t* input, int width, int height, uint8_t* output, int offset){
                
                unsigned int size = width*height;
		unsigned int k=size-1;		
		int threshold,highest=0,highestPos=0;
             
                
                
                unsigned int histo[8] = {0,0,0,0,0,0,0,0};               
                for (int h = height-1; h >= 0; h--) {
					for (int w = width-1; w >= 0; w--) {	
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
                    log_i("black background","threshold :%d\n",threshold);
                    //black background
                    threshold = (highestPos << 5) +32;                  
                    k=size-1;
                    for (int h = height-1; h >= 0; h--) {
			for (int w = width-1; w >= 0; w--) {			
                            output[k] = (input[k] < threshold + offset )? BACKGROUND:OBJECT;
                            k--;			
                        }
                    }
                    
                }
                else{
                    
                     //white background
                    threshold = highestPos << 5; 
                    log_i("white background","threshold :%d\n",threshold);
                    k=size-1;
                    for (int h = height-1; h >= 0; h--) {
			for (int w = width-1; w >= 0; w--) {			
                            output[k] = (input[k] > threshold- offset )? BACKGROUND:OBJECT;
                            k--;			
                        }
                    }
                }
                    
                
           
          
           
                 
             
    
}


void erosion3x3(uint8_t* input, int width, int height, uint8_t* output){
    
                int erosion[9] = {OBJECT, OBJECT, OBJECT, OBJECT, OBJECT, OBJECT, OBJECT, OBJECT, OBJECT};
                int sub[9];
                unsigned int i,j,pos;
		for(int i=height-2;i>=1;i--){
				for(int j=width-2;j>=1;j--){
					
					
										
						pos = (i+1)*(width-2)+(j);
						sub[6] =  input[pos-1] && erosion[6];
						sub[7] =  input[pos]   && erosion[7];					 
						sub[8] =  input[pos+1] && erosion[8];				 
											 		
						pos -= (width-2);
						sub[3] =  input[pos-1] && erosion[3];			 
						sub[5] =  input[pos+1] && erosion[5];	
						
						pos -= (width-2);					 		
						sub[0] =  input[pos-1] && erosion[0];
						sub[1] =  input[pos]   && erosion[1];					 
						sub[2] =  input[pos+1] && erosion[2];	
						
						pos += (width-2);
					
					if( sub[0] && sub[1] && sub[2] && sub[3] && sub[5] && sub[6] && sub[7] && sub[8]){
					
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
                unsigned int pos;
		int sub[9];
		for(int i=height-2;i>=1;i--){
				for(int j=width-2;j>=1;j--){
					
					
										
						pos = (i+1)*(width-2)+(j);
						sub[6] =  input[pos-1] && dilatation[6];
						sub[7] =  input[pos]   && dilatation[7];					 
						sub[8] =  input[pos+1] && dilatation[8];				 
											 		
						pos -= (width-2);
						sub[3] =  input[pos-1] && dilatation[3];			 
						sub[5] =  input[pos+1] && dilatation[5];	
						
						pos -= (width-2);					 		
						sub[0] =  input[pos-1] && dilatation[0];
						sub[1] =  input[pos]   && dilatation[1];					 
						sub[2] =  input[pos+1] && dilatation[2];	
						
						pos += (width-2);
					
					if(sub[0] || sub[1] || sub[2] || sub[3] || sub[5] || sub[6] || sub[7] ||sub[8]){
					
								output[pos] = OBJECT;
								
					}
					else{
								output[pos] = BACKGROUND; 
					}
					
	
			}
		}
    
}



int segMinX[200];
int segMinY[200];
int segMaxX[200];
int segMaxY[200];


unsigned int segmentation(uint8_t* input, int width, int height, uint8_t* output){
    
    unsigned int nbElement = 0;
    unsigned int ptJ,k,pos;
                                
    for(int i=height-3;i>=1;i--){
        for(int j=width-3;j>=1;j--){
		pos = (i)*(width-3)+(j);
		if(input[pos] == OBJECT){
                    
                        if(input[pos+1] == BACKGROUND){ //pixel suivant = backgroun
                                if(input[pos+(width-3)] == BACKGROUND){
                                        nbElement ++;
                                        output[pos] = nbElement;
                                        segMaxY[nbElement] = i;
                                        segMinY[nbElement] = i;
                                                                           
                                }
                                else{
                                    output[pos] = output[pos+(width-3)];
                                    segMinY[output[pos]] = i;
                                    
                                }			
                        }
                        else{
                                output[pos] = output[pos+1];   
                                
                                //on verifie que celui dans dessous a la meme couleur
                                if(output[pos+(width-3)] != BACKGROUND && output[pos] != output[pos+(width-3)]){
                                    k = pos;
                                    ptJ = 0;
                                    nbElement --;
                                    while( output[k] != BACKGROUND){
                                        output[k] = output[pos+(width-3)];
                                        k++;
                                        ptJ ++;
                                    }
                                    segMinY[output[pos]] = i;
                                    
                                   
                                }
                            
                                
                                
                                
                        } 
		}
		else{
			output[pos] = BACKGROUND;
		}
	}

    }


    for(int i=height-1;i>=0;i--){
        for(int j=width-1;j>=0;j--){
            
                    int pos = (i)*(width-1)+(j);
                    if(output[pos] != BACKGROUND){
                            
                        
                        segMaxX[output[pos]] = (segMaxX[output[pos]] < j)? j:segMaxX[output[pos]];
                        segMinX[output[pos]] = (segMinX[output[pos]] > j || segMinX[output[pos]] == 0)? j:segMinX[output[pos]];
                                
                    }
                   
                        
        }
    }   
    return nbElement;
}

int TabCircle[200];

int isCircle(uint8_t* input, int width, int height, int nbElement, uint8_t* output, int PARAM){
    
    int nbCircle=0;
    
    int midX,midY,radius1,radius2,newX1,newY1,newX2,newY2;
    int pos, sub[9];
    
    for(int i = nbElement; i >=1; i--){
        
        midY = (segMaxY[i] + segMinY[i]) >> 1;
        midX = (segMaxX[i] + segMinX[i]) >> 1;
        output[(midY)*(width-1)+(midX)] = 7;
        
        
        radius1 = (segMaxX[i] - segMinX[i]) >> 1;
        radius2 = (segMaxY[i] - segMinY[i]) >> 1;
      
        newX1 = midX + radius1 * 0.707106;
        newY1 = midY + radius1 * 0.707106;
        
        
        newX2 = midX + radius2 * 0.707106;
        newY2 = midY + radius2 * 0.707106;
        
        
        pos = (newY1+1)*(width-1)+(newX1);
        
	sub[6] =  input[pos-1];
	sub[7] =  input[pos];					 
        sub[8] =  input[pos+1];				 
											 		
	pos -= (width-1);
        
	sub[3] =  input[pos-1];
        sub[4] =  input[pos+1];
	sub[5] =  input[pos+1];	
						
	pos -= (width-1);
         
	sub[0] =  input[pos-1];
        sub[1] =  input[pos];					 
	sub[2] =  input[pos+1];
        
        if( (sub[0] || sub[1] || sub[2] || sub[3] || sub[4] || sub[5] || sub[6] ||sub[7] ||sub[8]) ){
            nbCircle ++;
            TabCircle[i] = 1;
        }
        else{
            
                    pos = (newY2+1)*(width-1)+(newX2);

                    sub[6] =  input[pos-1];
                    sub[7] =  input[pos];					 
                    sub[8] =  input[pos+1];				 

                    pos -= (width-1);

                    sub[3] =  input[pos-1];
                    sub[4] =  input[pos+1];
                    sub[5] =  input[pos+1];	

                    pos -= (width-1);

                    sub[0] =  input[pos-1];
                    sub[1] =  input[pos];					 
                    sub[2] =  input[pos+1];
                    if( (sub[0] || sub[1] || sub[2] || sub[3] || sub[4] || sub[5] || sub[6] ||sub[7] ||sub[8]) ){
                        nbCircle ++;
                        TabCircle[i] = 1;
                    }
            
        }
        
        
        
       
    }
    log_e("nbcircle = ","%d",nbCircle);
    pcDisplayCircle(input,width,height,0,0,TabCircle);
    
    
    

}






void borderDetector(uint8_t* input, int width, int height, uint8_t* output, int R ) {
		
                
                
                unsigned int size = (width)*(height);
                unsigned int k=size-1;	
		
		unsigned int  pos=0;
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
		
		for(int i=height-2;i>=1;i--){
			for(int j=width-2;j>=1;j--){	
                                                
						pos = (i+1)*(width-2)+(j);
                            
                                               
						sub[6] =  input[pos-1];
						sub[7] =  input[pos];					 
						sub[8] =  input[pos+1];				 
											 		
						pos -= (width-2);
						sub[3] =  input[pos-1];
						sub[4] =  input[pos];					 
						sub[5] =  input[pos+1];	
						
						pos -= (width-2);					 		
						sub[0] =  input[pos-1];
						sub[1] =  input[pos];					 
						sub[2] =  input[pos+1];				 
											 
					
						pos += (width-2);
						 
											 
						
						temp_h =0;
						temp_v =0;
						
						for(int l=8; l>=0; l--){
							//temp_h += (sub[l]*prewitt_H[l]);
							//temp_v += (sub[l]*prewitt_V[l]);
							
							temp_h += (sub[l]*sobel_H[l]);
							temp_v += (sub[l]*sobel_V[l]);
						}
						
						
						norm=temp_h*temp_h + temp_v*temp_v;
									
						
						output[pos] = (norm >= threshold)? OBJECT:BACKGROUND;
					
						
					}
                                        
                        
						
		}
		
	
}


void shapeDetector(uint8_t* input, int width, int height, uint8_t* output) {
		
                uint8_t tmp[614400];
                uint8_t tmp2[614400];
    
                thresholding(input, width,height, tmp,20);
		borderDetector(tmp,width,height,tmp2,28);
                dilation3x3(tmp2,width,height,tmp);
                
                erosion3x3(tmp,width,height,tmp2);
               
                unsigned int element = segmentation(tmp2,width,height,output);
                log_e("shapeDetector","nb element = %d",element);
                isCircle(output,width,height,element,output,0);
                
                
           
}