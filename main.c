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



uint8_t f1[614400];
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
		DecodeYUVtoY(videoFrame,f1,width,height);
		borderdetector2(f1,width,height,f2,5000);
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
    
        uint8_t * videoFrame = (uint8_t*)malloc(width*height*2);
        
    
        if(Testing){
            testFunction();
	} 
        else{
            process_image_yuv422 (videoFrame, width, height);
        }
           

    
    
}

