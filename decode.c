#include <stdint.h>				// uint_8		
#include "decode.h"


void DecodeYUVtoRGB(uint8_t * inFrame, uint8_t * outFrame ,int width, int height)
{
	
		static const int Precision = 32768;
		static const int CoefficientY =  (int)(1.164 * 32768 + 0.5);
		static const int CoefficientRV = (int)(1.596 * 32768 + 0.5);
		static const int CoefficientGU = (int)(0.391 * 32768 + 0.5);
		static const int CoefficientGV = (int)(0.813 * 32768 + 0.5);
		static const int CoefficientBU = (int)(2.018 * 32768 + 0.5);

		
		unsigned char Y1,Y2,U,V;
		
		int k = 0;
		int o = 0;
		
		for (int h = 0; h < height; h++) {
			for (int w = 0; w < width; w+=2) {	
				
					U  =  inFrame[k];
					Y1 =  inFrame[k+1];
					V  =  inFrame[k+2];
					Y2 =  inFrame[k+3];
					
					
					int R = CoefficientY * (Y1-16) + CoefficientRV * (V -128);
					int G = CoefficientY * (Y1-16) - CoefficientGU * (U -128) - CoefficientGV * (V -128) ;
					int B = CoefficientY * (Y1-16) + CoefficientBU * (U -128);
					
					R = (R + Precision / 2) / Precision;
					G = (G + Precision / 2) / Precision;
					B = (B + Precision / 2) / Precision;
					
					
					if (R < 0) R = 0;
					if (R > 255) R = 255;
					
					if (G < 0) G = 0;
					if (G > 255) G = 255;
					
					if (B < 0) B = 0;
					if (B > 255) B = 255;
					
					outFrame[o]= R;
					outFrame[o+1]= G;
					outFrame[o+2]= B;
					
					o+=3;					
					
					R = CoefficientY * (Y2-16) + CoefficientRV * (V -128);
					G = CoefficientY * (Y2-16) - CoefficientGU * (U -128) - CoefficientGV * (V -128) ;
					B = CoefficientY * (Y2-16) + CoefficientBU * (U -128);
					
					R = (R + Precision / 2) / Precision;
					G = (G + Precision / 2) / Precision;
					B = (B + Precision / 2) / Precision;
					
					
					if (R < 0) R = 0;
					if (R > 255) R = 255;
					
					if (G < 0) G = 0;
					if (G > 255) G = 255;
					
					if (B < 0) B = 0;
					if (B > 255) B = 255;
					
					outFrame[o]= R;
					outFrame[o+1]= G;
					outFrame[o+2]= B;
					
					o+=3;
					
					
					k +=4;
					
					
			}	
		}
		
}




void DecodeYUVtoY(uint8_t* inFrame, uint8_t* outFrame ,int width, int height)
{
	
		unsigned char Y1,Y2; //,U,V ;
		int k = height*width*2-1;
		int o = height*width-1;
		
		for (int h = height-1; h >= 0; h--) {
			for (int w = width-1; w >= 0; w-=2) {	
				
					//U  =  inFrame[k];
					//Y1 =  inFrame[k+1];
					//V  =  inFrame[k+2];
					//Y2 =  inFrame[k+3];
					
					Y1 =  inFrame[k-2];
					Y2 =  inFrame[k];
					
					outFrame[o-1]= Y1;
					outFrame[o]= Y2;
					
					o-=2;
					k-=4;
					
			}	
		}
		
}




