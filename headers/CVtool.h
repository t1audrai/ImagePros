#ifndef CVTOOL_H
#define CVTOOL_H 


struct matrix*  createPrewitt(const char* dir);


struct matrix* borderdetector( struct matrix*  input_m, struct matrix*  output_m, int threshold );


void borderdetector2(uint8_t* input, int width, int height, uint8_t* output, int threshold );
#endif

