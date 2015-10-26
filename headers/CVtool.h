#ifndef CVTOOL_H
#define CVTOOL_H 

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <getopt.h>             /* getopt_long() */
#include <unistd.h>
#include <stdint.h>
#include <sys/mman.h>
#include <sys/ioctl.h>
#include <linux/fb.h>


typedef struct 
{   int x;
    int y;
}Coordinates;


typedef struct {
    Coordinates max;
    Coordinates min; 
    Coordinates center;
    int radiusX;
    int radiusY;
    int value;
    int isCircle;
}Shape;


Shape shape[200];

void borderDetector(uint8_t* input, int width, int height, uint8_t* output, int threshold );
void shapeDetector(uint8_t* input, int width, int height, uint8_t* outputs);
int imageMean(uint8_t* input, int width, int height);

void thresholding(uint8_t* input, int width, int height, uint8_t* output, int backgroundPercent );
void dilation3x3(uint8_t* input, int width, int height, uint8_t* output);
void erosion3x3(uint8_t* input, int width, int height, uint8_t* output);
unsigned int segmentation(uint8_t* input, int width, int height, uint8_t* output);

#endif

