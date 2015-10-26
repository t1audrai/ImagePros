#include <stdint.h>				// uint_8		
#include "decode.h"
#include "CVtool.h"
#include "myPrint.h"
#include "pcDisplay.h"
#include "init.h"

////////////////////////// TOOL BOX ////////////////////////////////

const int BACKGROUND = 0;
const int OBJECT = 255;


const int prewitt_H[9] = { -1, -1, -1, 0, 0, 0, 1, 1, 1};		
const int prewitt_V[9] = { -1, 0, 1, -1, 0, 1, -1, 0, 1};
		
const int sobel_H[9] = { -1, -2, -1, 0, 0, 0, 1, 2, 1};		
const int sobel_V[9] = { -1, 0, 1, -2, 0, 2, -1, 0, 1};

const int MatDilation3x3[9] = {255, 255, 255, 255, 255, 255, 255, 255, 255};	
const int MatErosion3x3[9] = {255, 255, 255, 255, 255, 255, 255, 255, 255};




/////////////////////////////////////////////////////////////////////

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
    
                
                int sub[9];
                unsigned int width_2 = width-2;
                unsigned int i,j,pos;
		for(int i=height-2;i>=1;i--){
				for(int j=width_2;j>=1;j--){
					
					
										
						pos = (i+1)*(width_2)+(j);
						sub[6] =  input[pos-1] && MatErosion3x3[6];
						sub[7] =  input[pos]   && MatErosion3x3[7];					 
						sub[8] =  input[pos+1] && MatErosion3x3[8];				 
											 		
						pos -= (width_2);
						sub[3] =  input[pos-1] && MatErosion3x3[3];			 
						sub[5] =  input[pos+1] && MatErosion3x3[5];	
						
						pos -= (width_2);					 		
						sub[0] =  input[pos-1] && MatErosion3x3[0];
						sub[1] =  input[pos]   && MatErosion3x3[1];					 
						sub[2] =  input[pos+1] && MatErosion3x3[2];	
						
						pos += (width_2);
					
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

         
                unsigned int width_2 = width-2;
                unsigned int pos;
		int sub[9];
		for(int i=height-2;i>=1;i--){
				for(int j=width_2;j>=1;j--){
					
					
										
						pos = (i+1)*(width_2)+(j);
						sub[6] =  input[pos-1] && MatDilation3x3[6];
						sub[7] =  input[pos]   && MatDilation3x3[7];					 
						sub[8] =  input[pos+1] && MatDilation3x3[8];				 
											 		
						pos -= (width_2);
						sub[3] =  input[pos-1] && MatDilation3x3[3];			 
						sub[5] =  input[pos+1] && MatDilation3x3[5];	
						
						pos -= (width_2);					 		
						sub[0] =  input[pos-1] && MatDilation3x3[0];
						sub[1] =  input[pos]   && MatDilation3x3[1];					 
						sub[2] =  input[pos+1] && MatDilation3x3[2];	
						
						pos += (width_2);
					
					if(sub[0] || sub[1] || sub[2] || sub[3] || sub[5] || sub[6] || sub[7] ||sub[8]){
					
								output[pos] = OBJECT;
								
					}
					else{
								output[pos] = BACKGROUND; 
					}
					
	
			}
		}
    
}


unsigned int segmentation(uint8_t* input, int width, int height, uint8_t* output){
    
    unsigned int nbElement = 0;
    unsigned int ptJ,k,pos;
    unsigned int width_1 = width-1;
    unsigned int width_3 = width-3;
    
    for(int i=height-3;i>=1;i--){
        for(int j=width_3;j>=1;j--){
		pos = (i)*(width_3)+(j);
		if(input[pos] == OBJECT){
                    
                        if(input[pos+1] == BACKGROUND){ //pixel suivant = backgroun
                                if(input[pos+(width-3)] == BACKGROUND){
                                        nbElement ++;
                                        output[pos] = nbElement;
                                        shape[nbElement].max.y = i;
                                        shape[nbElement].min.y = i;
                                        shape[nbElement].value = nbElement;
                                        
                                                                           
                                }
                                else{
                                    output[pos] = output[pos+(width_3)];
                                    shape[output[pos]].min.y = i;
                                    
                                }			
                        }
                        else{
                                output[pos] = output[pos+1];   
                                
                                //on verifie que celui dans dessous a la meme couleur
                                if(output[pos+(width-3)] != BACKGROUND && output[pos] != output[pos+(width_3)]){
                                    k = pos;
                                    ptJ = 0;
                                    nbElement --;
                                    while( output[k] != BACKGROUND){
                                        output[k] = output[pos+(width_3)];
                                        k++;
                                        ptJ ++;
                                    }
                                    shape[nbElement+1].value = 0;
                                    shape[output[pos]].min.y = i;
                                   
                                }
                            
                                
                                
                                
                        } 
		}
		else{
			output[pos] = BACKGROUND;
		}
	}

    }


    for(int i=height-1;i>=0;i--){
        for(int j=width_1;j>=0;j--){
            
                    int pos = (i)*(width_1)+(j);
                    if(output[pos] != BACKGROUND){
                            
                        shape[output[pos]].max.x = (shape[output[pos]].max.x < j)? j:shape[output[pos]].max.x;
                        shape[output[pos]].min.x = (shape[output[pos]].min.x > j || shape[output[pos]].min.x == 0)? j:shape[output[pos]].min.x;                               
                    }
                   
                        
        }
    }   
    return nbElement;
}


int isCircle(uint8_t* input, int width, int height, int nbElement, uint8_t* output, int PARAM){
    
    int nbCircle=0;
    unsigned int width_1 = width-1;
    int newX1,newY1,newX2,newY2;
    int pos, sub[9];
    
    for(int i = nbElement; i >=1; i--){
           
        shape[i].center.y = (shape[i].max.y + shape[i].min.y) >> 1;
        shape[i].center.x = (shape[i].max.x + shape[i].min.x) >> 1;
        //output[(midY)*(width-1)+(midX)] = 7;
        
        
        shape[i].radiusX = (shape[i].max.x - shape[i].min.x) >> 1;
        shape[i].radiusY = (shape[i].max.y - shape[i].min.y) >> 1;
      
        newX1 = shape[i].center.x + RADxPI_4[shape[i].radiusX];
        newY1 = shape[i].center.y + RADxPI_4[shape[i].radiusX];
        
        
        newX2 = shape[i].center.x + RADxPI_4[shape[i].radiusY];// radius2 * 0.707106;
        newY2 = shape[i].center.y + RADxPI_4[shape[i].radiusY];//radius2 * 0.707106;
        
        
        pos = (newY1+1)*(width_1)+(newX1);
        
	sub[6] =  input[pos-1];
	sub[7] =  input[pos];					 
        sub[8] =  input[pos+1];				 
											 		
	pos -= (width_1);
        
	sub[3] =  input[pos-1];
        sub[4] =  input[pos];
	sub[5] =  input[pos+1];	
						
	pos -= (width_1);
         
	sub[0] =  input[pos-1];
        sub[1] =  input[pos];					 
	sub[2] =  input[pos+1];
        
        if( (sub[0] || sub[1] || sub[2] || sub[3] || sub[4] || sub[5] || sub[6] ||sub[7] ||sub[8]) ){
            nbCircle ++;
            shape[i].isCircle =1;
        }
        else{
            
                    pos = (newY2+1)*(width_1)+(newX2);

                    sub[6] =  input[pos-1];
                    sub[7] =  input[pos];					 
                    sub[8] =  input[pos+1];				 

                    pos -= (width_1);

                    sub[3] =  input[pos-1];
                    sub[4] =  input[pos+1];
                    sub[5] =  input[pos+1];	

                    pos -= (width_1);

                    sub[0] =  input[pos-1];
                    sub[1] =  input[pos];					 
                    sub[2] =  input[pos+1];
                    if( (sub[0] || sub[1] || sub[2] || sub[3] || sub[4] || sub[5] || sub[6] ||sub[7] ||sub[8]) ){
                        nbCircle ++;
                        shape[i].isCircle =1;
                    }
            
        }
        
        
        
       
    }
    log_e("nbcircle = ","%d",nbCircle);
    pcDisplayCircle(input,width,height,0,0);
    
    
    

}






void borderDetector(uint8_t* input, int width, int height, uint8_t* output, int R ) {
		
                
                
                unsigned int size = (width)*(height);
                unsigned int k=size-1;	
		unsigned int width_2 = width-2;
		unsigned int  pos=0;
		int temp_h=0,temp_v = 0;
		int norm = 0;
		
		double tmp_mean=0;
		uint8_t mean =0;
		
	
	
		int sub[9];
		
	
		int threshold = imageMean(input, width, height) * R;
		
		for(int i=height-2;i>=1;i--){
			for(int j=width-2;j>=1;j--){	
                                                
						pos = (i+1)*(width_2)+(j);
                            
                                               
						sub[6] =  input[pos-1];
						sub[7] =  input[pos];					 
						sub[8] =  input[pos+1];				 
											 		
						pos -= (width_2);
						sub[3] =  input[pos-1];
						sub[4] =  input[pos];					 
						sub[5] =  input[pos+1];	
						
						pos -= (width_2);					 		
						sub[0] =  input[pos-1];
						sub[1] =  input[pos];					 
						sub[2] =  input[pos+1];				 
											 
					
						pos += (width_2);
						 
											 
						
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