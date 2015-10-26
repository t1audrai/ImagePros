#ifndef CVTOOL_H
#define CVTOOL_H 


void borderDetector(uint8_t* input, int width, int height, uint8_t* output, int threshold );
void shapeDetector(uint8_t* input, int width, int height, uint8_t* outputs);
int imageMean(uint8_t* input, int width, int height);

void thresholding(uint8_t* input, int width, int height, uint8_t* output, int backgroundPercent );
void dilation3x3(uint8_t* input, int width, int height, uint8_t* output);
void erosion3x3(uint8_t* input, int width, int height, uint8_t* output);
unsigned int segmentation(uint8_t* input, int width, int height, uint8_t* output);

#endif

