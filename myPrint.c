#include "myPrint.h"
#include <string.h>
#include <sys/ioctl.h>
#include <stdarg.h>


void log_i(const char *msg, const char *input, ...){
		va_list args;
		if (msg[0] != '\0'){
			 fprintf(stderr, ANSI_COLOR_GREEN "Log.i : \"%s\" " ,msg);
		}
		else{
			fprintf(stderr, ANSI_COLOR_GREEN);	
		}
		va_start(args, input);
		vfprintf(stderr, input, args );
		va_end(args);
		fprintf(stderr, ANSI_COLOR_RESET "\n");
}


void log_e(const char *msg, const char *input, ...){
		va_list args;
		if (msg[0] != '\0'){
			 fprintf(stderr, ANSI_COLOR_RED "Log.e : \"%s\" " ,msg);
		}
		else{
			fprintf(stderr, ANSI_COLOR_RED);	
		}
		va_start(args, input);
		vfprintf(stderr, input, args );
		va_end(args);
		fprintf(stderr, ANSI_COLOR_RESET "\n");
}

void log_d(const char *msg, const char *input, ...){
		va_list args;
		
		if (msg[0] != '\0'){
			 fprintf(stderr, ANSI_COLOR_YELLOW "Log.d : \"%s\" " ,msg);
		}
		else{
			fprintf(stderr, ANSI_COLOR_YELLOW);	
		}
		va_start(args, input);
		vfprintf(stderr, input, args );
		va_end(args);
		fprintf(stderr, ANSI_COLOR_RESET);
}

void log_w(const char *msg, const char *input, ...){
		va_list args;
		if (msg[0] != '\0'){
			 fprintf(stderr, ANSI_COLOR_BLUE "Log.w : \"%s\" " ,msg);
		}
		else{
			fprintf(stderr, ANSI_COLOR_BLUE);	
		}
		va_start(args, input);
		vfprintf(stderr, input, args );
		va_end(args);
		fprintf(stderr, ANSI_COLOR_RESET "\n");
}


void log_wtf(const char *msg, const char *input, ...){
		va_list args;
		if (msg[0] != '\0'){
			 fprintf(stderr, ANSI_COLOR_MAGENTA "Log.wtf : \"%s\" " ,msg);
		}
		else{
			fprintf(stderr, ANSI_COLOR_MAGENTA);	
		}
		va_start(args, input);
		vfprintf(stderr, input, args );
		va_end(args);
		fprintf(stderr, ANSI_COLOR_RESET "\n");  
}






