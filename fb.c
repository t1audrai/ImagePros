/* File: fb.c */

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <getopt.h>             /* getopt_long() */
#include <unistd.h>
#include <stdint.h>				// uint_8
#include <sys/mman.h>
#include <sys/ioctl.h>
#include <linux/fb.h>


#include "myPrint.h"
#include "display.h"
#include "decode.h"
#include "CVtool.h"
#include "init.h"

typedef void (*ProcessFunc)(uint8_t *, int, int);

/* Device Name like /dev/fb */
#define FBNAME	"/dev/fb0"

/* fixed screen information */
struct fb_fix_screeninfo fix_info;

/* configurable screen info */
struct fb_var_screeninfo var_info;

/* The frame buffer memory pointer */
uint8_t *framebuffer;



/////////////////////////////////

#define YES 1;
#define NO 0;

//int Testing = YES;
int Testing = NO;


#define WIDTH 640;
#define HEIGHT 480;
#define SIZE 640*480*2;

uint8_t f1[614400];
uint8_t f3[614400];


//////////////////////////////////
/*
 * Macro to pack the pixel based on the rgb bit offset.
 * We compute each color value based on bit length
 * and shift it to its corresponding offset in the pixel.
 * each color component is 8 bits long
 *
 * For example: Considering a RGB565, the formula will
 * expand as:-
 * Red len=5, off=11 : Green len=6, off=6 : Blue len=5, off=0
 * pixel_value = ((red >> (8 - 5) << 11)|
 *       ((green >> (8 - 6) << 6) |
 *      ((blue >> (8 - 5) << 0)
 */
#define RGB(r,g,b) ( \
        (((r) >> (8-var_info.red.length)) << var_info.red.offset) | \
        (((g) >> (8-var_info.green.length)) << var_info.green.offset) | \
        (((b) >> (8-var_info.blue.length)) << var_info.blue.offset) \
)

#define SET_PIXEL(x,y,color) (((short*)framebuffer)[(x)+(y)*fix_info.line_length/2]=(color))

/* function to a filled rectangle at position (x,y), width w and height h */
/*void rect_fill(int x,int y, int w, int h, unsigned short color)
{
	int i, j;
	for (i=0;i<w;i++) {
		for (j=0;j<h;j++) {
			SET_PIXEL(x+i,y+j,color);
		}
	}
}*/

/***************************************************************************
 * decoding stuff
 ***************************************************************************/
#define bounds(m,M,x) ((x)>M ? M : (x)<(m) ? m : (x))


static void process_image_yuv422 (uint8_t * videoFrame, int width, int height)
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
		
		//borderdetector2(f1,width,height,f2,5000);
		//displayPictureRGB(f,width,height);
		
		//shapeDetector(f1,width,height,f3);
		hough(f1,width,height,f3);
		
		
		
		
	
		displayCircle(f3,f1,width,height,0,0);
		
		
       //displayPictureBlack(f2,width,height,0,height);
       //displayPictureFC(f2,width,height,0,0); 
       //displayCircle(f1,width,height,0,height);
		
					
               //hough(videoFrame,width,height,f1);
               //displayPictureBlack(f1,width,height,0,0);*/

}


static void process_image_raw12(uint8_t * videoFrame, int width, int height)
{
}

/***************************************************************************
 * main
 ***************************************************************************/
typedef enum 
{      
	PIX_FMT_YUV420P,
	PIX_FMT_RGB565,
	PIX_FMT_RGB32,
	PIX_FMT_YUV422,
	PIX_FMT_RAW12
} pix_fmt;

//needed to parse command line arguments with getopt_long
static const char short_options [] = "p:w:h";

//also needed to parse command line arguments with getopt_long
static const struct option
long_options [] = 
{
	{ "pixel-format",required_argument,      NULL,           'p' },
	{ "window-size", required_argument,      NULL,           'w' },
	{ "help",        no_argument,            NULL,           'h' },
	{ 0, 0, 0, 0 }
};

static void usage (FILE *fp, int argc, char **argv)
{
	fprintf (fp,
				"Usage: %s [options]\n\n"
				"Options:\n"
				"-p | --pixel-format   number          Pixel Format \n"
				"                                      (0 = YUV420P)\n"
				"                                      (1 = RGB565 )\n"                 
				"                                      (2 = RGB32  )\n"  
				"                                      (3 = YUV422 )\n" 
				"                                      (4 = raw12  )\n" 
				
				"-w | --window-size    <640*480|       Video size\n"
				"                       320*240>\n"
				"-h | --help                           Print this message\n"
				"\n",
				argv[0]);
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



int main(int argc, char *argv[])
{
    int size;

	int					fbd;			/* Frame buffer descriptor */

	int                 width                = WIDTH;
	int                 height               = HEIGHT;
	int                 index;
	int                 c;
	pix_fmt             pixel_format = PIX_FMT_YUV422;
	ProcessFunc			proc_func=process_image_yuv422;
	
	int					quit=0;

	init_compute();
	if(Testing){
			testFunction();
	} 
	
	while(1) {
		c = getopt_long (argc, argv, short_options, long_options, &index);

		if (-1 == c)
			break; //no more arguments

		switch (c) {
			case 0: // getopt_long() flag
				break;

			case 'p':
				pixel_format = (pix_fmt) atoi(optarg);
       			switch(pixel_format) {
				case PIX_FMT_YUV422:
					proc_func=process_image_yuv422;
					break;
				case PIX_FMT_RAW12:
					proc_func=process_image_raw12;
					break;
				default:
					fprintf(stderr, "\n\nError: Pixel format NOT supported\n\n");
					exit (EXIT_FAILURE);
				}
				break;

			case 'w':
				sscanf(optarg,"%d*%d",&width,&height);
				fprintf(stderr,"window size %d*%d\n",width,height);
				break;

			case 'h':
				usage (stdout, argc, argv);
				exit (EXIT_SUCCESS);

			default:
				usage (stderr, argc, argv);
				exit (EXIT_FAILURE);
		}
	}

    /* Open the framebuffer device in read write */
    fbd = open(FBNAME, O_RDWR);
    if (fbd < 0) {
        fprintf(stderr, "Unable to open %s.\n", FBNAME);
        return EXIT_FAILURE;
    }

    /* Do Ioctl. Retrieve fixed screen info. */
    if (ioctl(fbd, FBIOGET_FSCREENINFO, &fix_info) < 0) {
        fprintf(stderr, "get fixed screen info failed: %s\n",
        	strerror(errno));
        close(fbd);
        return EXIT_FAILURE;
    }

    /* Do Ioctl. Get the variable screen info. */
	if (ioctl(fbd, FBIOGET_VSCREENINFO, &var_info) < 0) {
        fprintf(stderr, "Unable to retrieve variable screen info: %s\n",
	    	strerror(errno));
        close(fbd);
        return EXIT_FAILURE;
    }

    /* Print some screen info currently available */
    fprintf(stderr, "Screen resolution: (%dx%d)\n",var_info.xres,var_info.yres);
	fprintf(stderr, "x offset, y offset : %d, %d\n",var_info.xoffset,var_info.yoffset);
    fprintf(stderr, "Line width in bytes %d\n", fix_info.line_length);
    fprintf(stderr, "bits per pixel : %d\n", var_info.bits_per_pixel);
    fprintf(stderr, "Red: length %d bits, offset %d\n",var_info.red.length,var_info.red.offset);
	fprintf(stderr, "Green: length %d bits, offset %d\n",var_info.red.length, var_info.green.offset);
    fprintf(stderr, "Blue: length %d bits, offset %d\n",var_info.red.length,var_info.blue.offset);
	/* Calculate the size to mmap */
	size=fix_info.line_length * var_info.yres;

	/* Now mmap the framebuffer. */
	framebuffer = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_SHARED, fbd,0);
    if (framebuffer == NULL) {
        fprintf(stderr, "mmap failed:\n");
        close(fbd);
        return EXIT_FAILURE;
    }

    fprintf(stderr, "framebuffer mmap address=%p\n", framebuffer);
    fprintf(stderr, "framebuffer size=%d bytes\n", size);

    uint8_t * videoFrame = (uint8_t*) malloc (width*height*2);
	if (!videoFrame) {
		fprintf(stderr, "could not allocate buffer for video frame (%d bytes required)\n", width*height*2);
		exit (EXIT_FAILURE);
	}
	
	

    while (!quit && !Testing)
    {
		
		uint8_t *ptr=videoFrame;
		int size=width*height*2;
		while(size) {
			int ret = read(STDIN_FILENO, ptr , size);
			ptr+=ret;
			size-=ret;
			
		}
		
		
		proc_func(videoFrame, width, height);
		
	}

    /* Release mmap. */
    munmap(framebuffer,0);
    close(fbd);
    return EXIT_SUCCESS;
}

