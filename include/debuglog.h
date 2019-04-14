#ifndef __DEBUGLOG__
#define __DEBUGLOG__

#include <stdio.h>
#include <stdlib.h>
#define DEBUG
#ifdef DEBUG

#define ENTER_FUNCTION printf("ENTER_FUNCTION:%s, %d\n\r", __FUNCTION__, __LINE__)
#define OUT_FUNCTION printf("OUT_FUNCTION:%s, %d\n\r", __FUNCTION__, __LINE__)
#define LOG_PRINT(msg, args...) \
{   \
fprintf(stdout, "LOG=>FUNCTION:%s LINE:%d->", __FUNCTION__, __LINE__); \
fprintf(stdout, msg, ##args); \
}

#define LOG_ERR(msg, args...) \
{   \
fprintf(stderr, "ERROR=>FUNCTION:%s LINE:%d->", __FUNCTION__, __LINE__); \
fprintf(stderr, msg, ##args); \
}
#else

#define ENTER_FUNCTION
#define OUT_FUNCTION
#define LOG_PRINT
#define LOG_ERR

#endif
#endif

