/* 
 * File:   main.c
 * Author: t1audrai
 *
 * Created on 20 octobre 2015, 00:34
 */


#include "myPrint.h"
#include "display.h"
#include "pcDisplay.h"
#include "decode.h"
#include "CVtool.h"
#include "init.h"
#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <opencv/highgui.h>



/*
 * 
 */
    
#define YES 1;
#define NO 0;

//int Testing = YES;
int Testing = NO;


#define WIDTH 640;
#define HEIGHT 480;
#define SIZE 640*480*2;



uint8_t outVideo[3000000];
uint8_t f2[614400];





static void process_image_yuv422(uint8_t * videoFrame, int width, int height)
{
	
/*              x
		0 1 2 3 4 5 6 7
		
	0	G R G R G R G R
	1	B G B G B G B G
y	2	G R G R G R G R
	3	B G B G B G B G
	4	G R G R G R G R
	5	B G B G B G B G

 */
		
		
		
		//DecodeYUVtoRGB(videoFrame,f,width,height);
		//DecodeYUVtoY(videoFrame,f1,width,height);
    
    
               //borderDetector(videoFrame,width,height,outVideo,28);
               //pcDisplayPictureBlack(outVideo,width,height,0,0); 
                
              shapeDetector(videoFrame,width,height,outVideo);
              // pcDisplayPictureFC(outVideo,width,height,0,0);
              pcDisplayCircle(outVideo,videoFrame,width,height,0,0);
                
       
    
               //hough(videoFrame,width,height,outVideo);
               //pcDisplayPictureBlack(outVideo,width,height,0,0);
		
		//displayPictureBlack(f2,width,height);
		
                //displayPictureRGB(f,width,height);
		
					

}



void testFunction(){
	                                             
		 log_d("","\n");
		 log_d("","    _           _   _____             _   _          \n");
		 log_d("","   | |_ ___ ___| |_|   __|_ _ ___ ___| |_|_|___ ___  \n");
		 log_d("","   |  _| -_|_ -|  _|   __| | |   |  _|  _| | . |   | \n");
		 log_d("","   |_| |___|___|_| |__|  |___|_|_|___|_| |_|___|_|_| \n");
		 log_d("","\n");                                                     

		
		
		
		
	
};



int main(int argc, char** argv) {
    
    
        int width  = WIDTH;
	int height = HEIGHT;
    

       
 
    
        if(Testing){ testFunction();} 
        else{
            
              IplImage* imgGray = NULL; 
              IplImage* imgRGB = NULL; 
              
              
              const char* window_title = "Hello, OpenCV!";
              
              //log_i("computing","");
              init_compute();
              //log_i("end computing","");
              
              
              imgGray = cvLoadImage("/root/Documents/Projet Elec/ImagePros/Images/test2.jpg", CV_LOAD_IMAGE_GRAYSCALE);
              imgRGB = cvLoadImage("/root/Documents/Projet Elec/ImagePros/Images/test2.jpg", CV_LOAD_IMAGE_COLOR);
              
              
              if (imgGray == NULL)
              {
                  fprintf (stderr, "couldn't open image file: %s\n", argv[1]);
                  return EXIT_FAILURE;
              }
              cvNamedWindow (window_title, CV_WINDOW_AUTOSIZE);
             
             
              height = imgGray->height;
              width = imgGray->width;
              
             uint8_t * videoFrame = (uint8_t*)malloc(width*height*2*sizeof(uint8_t));

              
  
             
             int i =0;
             for (int h = 0; h < height-1; h++) {
			for (int w = 0; w < width-1; w++){
                                    videoFrame[i++] = CV_IMAGE_ELEM(imgGray,uint8_t,h,w);
                                    
                        }
             }
             
              
             
            
            process_image_yuv422(videoFrame, width, height);
             
             
            i = 0;
            int j=0;
      
          
            for (int h = 0; h < height-1; h++) {
			for (int w = 0; w <( width-1)*3; w+=3){
                            
                                   CV_IMAGE_ELEM(imgRGB,uint8_t,h,w)   = outScreen[j++] ;//R
                                   CV_IMAGE_ELEM(imgRGB,uint8_t,h,w+1) = outScreen[j++]; //G
                                   CV_IMAGE_ELEM(imgRGB,uint8_t,h,w+2) = outScreen[j++];//B
                        }
             }
              
              cvShowImage (window_title, imgRGB);
              cvWaitKey(0);
              cvDestroyAllWindows();
              cvReleaseImage(&imgRGB);
            }
           

    
    
}

