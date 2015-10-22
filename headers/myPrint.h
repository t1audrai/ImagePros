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










#endif

