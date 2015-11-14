//#define PC
//#define BEAGLE


/* File: fb.c */
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <getopt.h>             /* getopt_long() */
#include <unistd.h>
#include <stdint.h> 

#include "myPrint.h"
#include "display.h"
#include "decode.h"
#include "CVtool.h"
#include "init.h"

#include <sys/stat.h>
#include <errno.h>


typedef void (*ProcessFunc)(uint8_t *, int, int);

typedef void (*CVprocessFunc)(uint8_t *, int, int, int, int, int, int, int);
CVprocessFunc cVprocessFunc;
int cVprocessArg[8];

#ifdef PC
#include <opencv/highgui.h> 
#include <sys/time.h>
#endif

#ifdef BEAGLE                              // uint_8
#include <sys/mman.h>
#include <sys/ioctl.h>
#include <linux/fb.h>


/* Device Name like /dev/fb */
#define FBNAME	"/dev/fb0"

/* fixed screen information */
struct fb_fix_screeninfo fix_info;

/* configurable screen info */
struct fb_var_screeninfo var_info;

/* The frame buffer memory pointer */
uint8_t *framebuffer;

#endif

/////////////////////////////////

#define YES 1;
#define NO 0;

//int Testing = YES;
int Testing = NO;


#define WIDTH 640;
#define HEIGHT 480;
#define SIZE 640*480*2;

uint8_t f1[614400];
uint8_t f2[614400];
uint8_t f3[614400];
uint8_t blackPicture[614400];
//fifo
#define MAX_BUF 1024
char buf[MAX_BUF];
int fd;



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
#ifdef BEAGLE  
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


#endif




static void process_image_hough(uint8_t * videoFrame, int width, int height, int thresholdBorder, int radMin, int RadMax, int step, int threshold){
    
        hough(videoFrame,width,height,f1,thresholdBorder,radMin,RadMax, step, threshold);
        displayCircle(f1,videoFrame,width,height,0,0);
     
}

static void process_image_shape(uint8_t * videoFrame, int width, int height, int thresholdSeg, int thresholdBorder, int step, int a, int b)
{
               unsigned int element = 0;
               unsigned int nbCircle =0;
               
		switch (step) {
			case 0: //image noir et blanc
                                log_e("image noir et blanc","");
                                displayPictureBlack(videoFrame,width,height,0,0);
				break;

                        case 1: //threshold
                                log_e("threshold","");
                                thresholding(videoFrame,width,height,f2,thresholdSeg);
                                displayPictureBlack(f2,width,height,0,0);
				break;
                                
                        case 2: //contour
                                log_e("contour","");
                                thresholding(videoFrame,width,height,f2,thresholdSeg);
                                borderDetector(f2,width,height,f3,thresholdBorder);
                                displayPictureBlack(f3,width,height,0,0);
				break;
                                
                        case 3: //dilatation
                                log_e("dilatation","");
                                thresholding(videoFrame,width,height,f2,thresholdSeg);
                                borderDetector(f2,width,height,f3,thresholdBorder);
                                dilation3x3(f3,width,height,f1);
                                displayPictureBlack(f1,width,height,0,0);
				break;
                                
                        case 4: //erosion
                                log_e("erosion","");
                                thresholding(videoFrame,width,height,f2,thresholdSeg);
                                borderDetector(f2,width,height,f3,thresholdBorder);
                                dilation3x3(f3,width,height,f1);
                                erosion3x3(f1,width,height,f2);
                                displayPictureBlack(f2,width,height,0,0);
				break;
                                
                        case 5: //segmentation
                                log_e("segmentation","");
                                thresholding(videoFrame,width,height,f2,thresholdSeg);
                                borderDetector(f2,width,height,f3,thresholdBorder);
                                dilation3x3(f3,width,height,f1);
                                erosion3x3(f1,width,height,f2);
                                element = segmentation(f2,width,height,f3);
                                log_i("shapeDetector","nb element = %d",element);
                                displayPictureFC(f3,width,height,0,0);
				break;
                                
                        case 6: //detection de cercle
                                log_e("detection de cercle","");
                                thresholding(videoFrame,width,height,f2,thresholdSeg);
                                borderDetector(f2,width,height,f3,thresholdBorder);
                                dilation3x3(f3,width,height,f1);
                                erosion3x3(f1,width,height,f2);
                                element = segmentation(f2,width,height,f3);
                                log_i("shapeDetector","nb element = %d",element);
                                nbCircle = isCircle(f3,width,height,element,0);
                                log_i("nbcircle = ","%d",nbCircle);
                                displayCircle(f3,f3,width,height,0,0);
				break;
                                
                                
                        case 7: //detection de cerlce avec le fond
                                log_e("detection de cerlce avec le fond","");
                                thresholding(videoFrame,width,height,f2,thresholdSeg);
                                borderDetector(f2,width,height,f3,thresholdBorder);
                                dilation3x3(f3,width,height,f2);
                                erosion3x3(f2,width,height,f3);
                                element = segmentation(f3,width,height,f2);
                                log_i("shapeDetector","nb element = %d",element);
                                nbCircle = isCircle(f2,width,height,element,0);
                                log_i("nbcircle = ","%d",nbCircle);
                                displayCircle(f2,videoFrame,width,height,0,0);
				break;
			
                        default:
                                log_e("erreur param step","");
                                break; 
                            
                                
            
                }
             
}    
                



static void process_image_yuv422 (uint8_t * videoFrame, int width, int height)
{
		DecodeYUVtoY(videoFrame,blackPicture,width,height);
         
}


static void process_image_raw12(uint8_t * videoFrame, int width, int height)
{
}

/***************************************************************************
 * main
 ***************************************************************************/
#ifdef BEAGLE  
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
#endif  

void testFunction(){
	                                             
		 log_d("","\n");
		 log_d("","    _           _   _____             _   _          \n");
		 log_d("","   | |_ ___ ___| |_|   __|_ _ ___ ___| |_|_|___ ___  \n");
		 log_d("","   |  _| -_|_ -|  _|   __| | |   |  _|  _| | . |   | \n");
		 log_d("","   |_| |___|___|_| |__|  |___|_|_|___|_| |_|___|_|_| \n");
		 log_d("","\n");                                                     
	
};

int communication(char * fifo){
	
			read(fd, buf, MAX_BUF);
		   	
                        if( buf[0] != '\0'){ //on a recu un nouvelle trame
                                    printf("Received: %s\n", buf);
                                    char tmp[512];
                                    int funct;
                                    //reading buffer;
                                    int i = 0, j=0,k=0;
                                    while(buf[i] != '\0'){
                                        j=0;
                                        while(buf[i] != ' '){
                                              tmp[j++] = buf[i++];
                                              
                                        }
                                        tmp[j] = '\0';
                                        i++;
                                        
                                        if(k==0){//la fonction
                                          sscanf(tmp,"%d",&funct);
                                        }
                                        else{                                       

                                          sscanf(tmp,"%d",&cVprocessArg[k]);
                                        }
                                        k++;
                                        
                                    }
                                   printf("funct: %d\n", funct);   
                                   printf("param[1]: %d\n", cVprocessArg[1]);
                                   printf("param[2]: %d\n", cVprocessArg[2]);
                                   printf("param[3]: %d\n", cVprocessArg[3]);
                                   printf("param[4]: %d\n", cVprocessArg[4]);
                                   printf("param[4]: %d\n", cVprocessArg[5]);
                       
                                   buf[0] = '\0';
                                   
                                  
                                 
                               
                                switch(funct) {
                                        case 1:
                                            printf("SHAPE %s\n");   
                                            cVprocessFunc=process_image_shape;
                                            break;
                                        case 2:
                                            printf("HOUGH %s\n"); 
                                            cVprocessFunc=process_image_hough;
                                            break;
                                        default:
                                            fprintf(stderr, "\n\nError: Function inconnue\n\n");
                                            exit (EXIT_FAILURE);
				}
			
                                   
                                   
                        }
                        
                        
                        
                        //process_image_shape(uint8_t * videoFrame, int width, int height, int step, int thresholdSeg, int thresholdBorder)
}


#ifdef BEAGLE  

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

#endif  


#ifdef PC  
int main(int argc, char** argv) {
            
        int width  = WIDTH;
	int height = HEIGHT;
        
        char * myfifo = "/tmp/myfifo";
    	unlink(myfifo);
	mkfifo(myfifo, 0666);
        
   

	fd = open(myfifo, O_RDONLY);
    

        if(Testing){ testFunction();} 
        else{
            
              IplImage* imgGray     = NULL; 
              IplImage* imgRGB      = NULL; 
              IplImage* imgYUV422   = NULL; 
              
              const char* window_title = "Hello, OpenCV!";
              
              //log_i("computing","");
              init_compute();
              //log_i("end computing","");
              
              
             
              imgRGB = cvLoadImage("/root/Documents/Projet Elec/ImagePros/Images/test2.jpg", CV_LOAD_IMAGE_COLOR);
              imgGray = cvLoadImage("/root/Documents/Projet Elec/ImagePros/Images/test2.jpg", CV_LOAD_IMAGE_GRAYSCALE);
              imgYUV422 = cvLoadImage("/root/Documents/Projet Elec/ImagePros/Images/test2.jpg", CV_LOAD_IMAGE_COLOR);
              
              if (imgYUV422 == NULL)
              {
                  fprintf (stderr, "couldn't open image file: %s\n", argv[1]);
                  return EXIT_FAILURE;
              }
              cvNamedWindow (window_title, CV_WINDOW_AUTOSIZE);
             
             
              height = imgYUV422->height;
              width = imgYUV422->width;
              
              
             //uint8_t * videoFrame = (uint8_t*)malloc(width*height*4*sizeof(uint8_t));
              uint8_t * videoFrame = (uint8_t*) malloc (width*height*2);
              
             cvCvtColor(imgRGB, imgYUV422,CV_RGB2YCrCb);
         
            
             int i =0;
             for (int h = 0; h < height-1; h++) {
			for (int w = 0; w < width-1; w++){
                                   videoFrame[i++] = CV_IMAGE_ELEM(imgGray,uint8_t,h,w);
                                   videoFrame[i++] = CV_IMAGE_ELEM(imgGray,uint8_t,h,w);
                                 
                                    
                                    
                        }
             }
             
            int fps = 0;
           
            struct timeval tvBegin, tvEnd, tvDiff;


            while(cvWaitKey(200) != 113){
                
                        gettimeofday(&tvBegin, NULL);
                        
                        
                        ProcessFunc proc_func=process_image_yuv422;
                        proc_func=process_image_yuv422;
                        proc_func(videoFrame, width, height);
                        communication(myfifo);
                        cVprocessFunc(blackPicture, width, height,cVprocessArg[1],cVprocessArg[2],cVprocessArg[3],cVprocessArg[4],cVprocessArg[5]);


                        i = 0;
                        int j=0;


                        for (int h = 0; h < height-1; h++) {
                                    for (int w = 0; w <( width-1)*3; w+=3){

                                               CV_IMAGE_ELEM(imgRGB,uint8_t,h,w)   = outScreen[j++] ;//R
                                               CV_IMAGE_ELEM(imgRGB,uint8_t,h,w+1) = outScreen[j++]; //G
                                               CV_IMAGE_ELEM(imgRGB,uint8_t,h,w+2) = outScreen[j++];//B
                                    }
                         }

                        cvShowImage(window_title, imgRGB);
                        gettimeofday(&tvEnd, NULL);
                        
                       
                        long int diff = (tvEnd.tv_usec + 1000000 * tvEnd.tv_sec) - (tvBegin.tv_usec + 1000000 * tvBegin.tv_sec);
                        tvDiff.tv_sec = diff / 1000000;
                        tvDiff.tv_usec = diff % 1000000;

   
                        
                        //printf("%ld.%06ld\n", tvDiff.tv_sec, tvDiff.tv_usec);
                        
                        printf("fps : %f\n", 1/(tvDiff.tv_sec + tvDiff.tv_usec*0.000001));
                   
             }
             
              cvDestroyAllWindows();
              cvReleaseImage(&imgRGB);
            }
           

    
    
}
#endif 