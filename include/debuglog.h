#ifndef __DEBUGLOG__
#define __DEBUGLOG__

#include <stdio.h>
#include <stdlib.h>
#define DEBUG
#ifdef DEBUG

#define ENTER_FUNCTION printf("ENTER=>%s:%s, %d\n\r",__FILE__, __FUNCTION__, __LINE__)
#define OUT_FUNCTION printf("OUT=>%s:%s, %d\n\r",__FILE__, __FUNCTION__, __LINE__)
#define LOG_PRINT(msg, args...) \
{   \
fprintf(stdout, "LOG=>%s:%s LINE:%d->", __FILE__, __FUNCTION__, __LINE__); \
fprintf(stdout, msg, ##args); \
}

#define LOG_ERR(msg, args...) \
{   \
fprintf(stderr, "ERROR=>%s:%s LINE:%d->", __FILE__, __FUNCTION__, __LINE__); \
fprintf(stderr, msg, ##args); \
}
#else

#define ENTER_FUNCTION
#define OUT_FUNCTION
#define LOG_PRINT
#define LOG_ERR

#endif
#endif

