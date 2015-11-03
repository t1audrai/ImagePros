#ifndef DISPLAY_H
#define DISPLAY_H 


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



/* configurable screen info */
struct fb_var_screeninfo var_info;

/* fixed screen information */
struct fb_fix_screeninfo fix_info;

/* The frame buffer memory pointer */
uint8_t *framebuffer;

#define RGB(r,g,b) ( \
        (((r) >> (8-var_info.red.length)) << var_info.red.offset) | \
        (((g) >> (8-var_info.green.length)) << var_info.green.offset) | \
        (((b) >> (8-var_info.blue.length)) << var_info.blue.offset) \
)

#define SET_PIXEL(x,y,color) (((short*)framebuffer)[(x)+(y)*fix_info.line_length/2]=(color))


#define B(pos)  ((myColor[pos] & 0xFF0000) >> 16)
#define G(pos)  ((myColor[pos] & 0x00FF00) << 8 >> 16)
#define R(pos)  ((myColor[pos] & 0x0000FF) << 16>> 16) 


void rect_fill(int x,int y, int w, int h, unsigned short color);
void displayPictureBlack(uint8_t * inFrame,int width, int height, int X_offset, int Y_offset);
void displayPictureRGB(uint8_t * inFrame,int width, int height);
void displayPictureFC(uint8_t * inFrame,int width, int height, int X_offset, int Y_offset);
void displayCircle(uint8_t * inFrame,int width, int height, int X_offset, int Y_offset);


#endif

