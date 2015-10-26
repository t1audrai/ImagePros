#ifndef MYPRINT_H
#define MYPRINT_H 
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>


#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"


void log_i(const char *msg, const char *input, ...);
void log_e(const char *msg, const char *input, ...);
void log_d(const char *msg, const char *input, ...);
void log_w(const char *msg, const char *input, ...);
void log_wtf(const char *msg, const char *input, ...);




static inline void loadBar(int x, int n, int r, int w){
    
    /// x the current index we are on
    /// n the number of indicies to process
    /// r the number of times we want to update the display 
    /// w for the width of the bar
     

    
    // Only update r times.
    if ( x % (n/r +1) != 0 ) return;
 
    // Caluate the ratio of complete-to-incomplete.
    float ratio = x/(float)n;
    int   c     = ratio * w;
 
    // Show the percentage complete.
    printf("%3d%% [", (int)(ratio*100) );
 
    // Show the load bar.
    for (int x=0; x<c; x++)
       printf("=");
 
    for (int x=c; x<w; x++)
       printf(" ");
 
    // ANSI Control codes to go back to the
    // previous line and clear it.
    printf("]\n\033[F\033[J");
}







#endif

