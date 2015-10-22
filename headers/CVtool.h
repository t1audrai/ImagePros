#ifndef CVTOOL_H
#define CVTOOL_H 


void borderDetector(uint8_t* input, int width, int height, uint8_t* output, int threshold );
void shapeDetector(uint8_t* input, int width, int height, uint8_t* output, int R );
int imageMean(uint8_t* input, int width, int height);

void thresholding(uint8_t* input, int width, int height, uint8_t* output, int backgroundPercent );

#endif

