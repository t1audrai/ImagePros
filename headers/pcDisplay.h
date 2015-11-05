/* 
 * File:   pcDisplay.h
 * Author: root
 *
 * Created on October 25, 2015, 2:12 PM
 */

#ifndef PCDISPLAY_H
#define	PCDISPLAY_H

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

uint8_t outScreen[3000000];



#define B(pos)  ((color[pos] & 0xFF0000) >> 16)
#define G(pos)  ((color[pos] & 0x00FF00) << 8 >> 16)
#define R(pos)  ((color[pos] & 0x0000FF) << 16>> 16) 


void pcDisplayPictureRGB(uint8_t * inFrame,int width, int height, int X_offset, int Y_offset);
void pcDisplayPictureBlack(uint8_t * inFrame,int width, int height, int X_offset, int Y_offset);
void pcDisplayPictureFC(uint8_t * inFrame,int width, int height, int X_offset, int Y_offset);
void pcDisplayCircle(uint8_t * inFrame,int width, int height, int X_offset, int Y_offset);

#endif	/* PCDISPLAY_H */

