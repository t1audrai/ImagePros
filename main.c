/* 
 * File:   main.c
 * Author: t1audrai
 *
 * Created on 20 octobre 2015, 00:34
 */


#include "myPrint.h"
#include "display.h"
#include "decode.h"
#include "CVtool.h"
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


int color[5] = {0x000000 ,0xFF0012, 0x00FF40, 0x0010FF, 0x7800FF};


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
                 
                shapeDetector(videoFrame,width,height,outVideo,5);
                 
                
       
		
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

		/*
		log_d("testFunction","test mult");
		log_d ("testFunction","ma");
		unsigned int * A = (unsigned int*) malloc (2*3* sizeof(unsigned int));
		A[0] =1;
		A[1] =2;
		A[2] =0;
		A[3] =4;
		A[4] =3;
		A[5] =1;
		struct matrix* MA = init_matrix(2,3,A);
		print_matrix(MA);


		log_d ("testFunction","mb\n");
		unsigned int * B = (unsigned int*) malloc (3*2* sizeof(unsigned int));
		B[0] =5;
		B[1] =1;
		B[2] =2;
		B[3] =3;
		B[4] =3;
		B[5] =4;
		struct matrix* MB = init_matrix(3,2,B);
		print_matrix(MB);
	
	
		log_d ("testFunction", "ans\n");
		struct matrix* ans = mult_matrix(MA,MB);
		print_matrix(ans);
		log_d ("testFunction", "\n");
		log_d ("testFunction", "ok2\n");
		
		*/
		/*
		log_d("testFunction","sous matrice\n");
		log_d ("testFunction","ma\n");
		int * A = (int*) malloc (2*3* sizeof(int));
		A[0] =1;
		A[1] =2;
		A[2] =0;
		A[3] =4;
		A[4] =3;
		A[5] =1;
		struct matrix* MA = init_matrix(2,3,A);
		print_matrix(MA);
		
		
		log_d ("testFunction","ans\n");
		struct matrix* ans = sub_matrix(MA,0,1,0,1);
		print_matrix(ans);
	
		unsigned int add = sum_matrix(ans);
		log_d ("testFunction","add = %d\n", add );
		log_i ("testFunction","add = %d\n", add );
		log_e ("testFunction","add = %d\n", add );
		log_wtf ("testFunction","add = %d\n", add );
		*/
		/*
		log_d("testFunction","Prewitt\n");
		struct matrix* ans = createPrewitt("H");
		print_matrix(ans);
		
		delete_matrix(ans);
		log_d("testFunction","del\n");*/
		
		
		
	
};



int main(int argc, char** argv) {
    
    
        int width  = WIDTH;
	int height = HEIGHT;
    

       
 
    
        if(Testing){ testFunction();} 
        else{
            
              IplImage* imgGray = NULL; 
              IplImage* imgRGB = NULL; 
              
              
              const char* window_title = "Hello, OpenCV!";
              imgGray = cvLoadImage("/root/Documents/Projet Elec/ImagePros/Images/shape.jpg", CV_LOAD_IMAGE_GRAYSCALE);
              imgRGB = cvLoadImage("/root/Documents/Projet Elec/ImagePros/Images/shape.jpg", CV_LOAD_IMAGE_COLOR);
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
             uint8_t R=0,B=0,G=0;
          
            for (int h = 0; h < height-1; h++) {
			for (int w = 0; w <( width-1)*3; w+=3){
                            
                                   B = (color[outVideo[i]] & 0xFF0000) >> 16;
                                   G = (color[outVideo[i]] & 0x00FF00) << 8 >> 16;
                                   R = (color[outVideo[i++]] & 0x0000FF) << 16>> 16;  
                                   CV_IMAGE_ELEM(imgRGB,uint8_t,h,w)   = R ; //R
                                   CV_IMAGE_ELEM(imgRGB,uint8_t,h,w+1) = G; //G
                                   CV_IMAGE_ELEM(imgRGB,uint8_t,h,w+2) = B;//B
                        }
             }
              
              cvShowImage (window_title, imgRGB);
              cvWaitKey(0);
              cvDestroyAllWindows();
              cvReleaseImage(&imgRGB);
            }
           

    
    
}

