#ifndef DECODE_H
#define DECODE_H 

#include <stdint.h>				// uint_8

void DecodeYUVtoRGB(uint8_t * inFrame, uint8_t * outFrame ,int width, int height);
void DecodeYUVtoY(uint8_t * inFrame, uint8_t * outFrame ,int width, int height);


#endif





