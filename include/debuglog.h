#ifndef __DEBUG_LOG__
#define __DEBUG_LOG__

#include <stdio.h>
#include <stdlib.h>

#ifdef _DEBUG

#define ENTER_FUNCTION fprintf(stdout, "ENTER=>%s:%s, %d\n\r",__FILE__, __FUNCTION__, __LINE__)
#define EXIT_FUNCTION fprintf(stdout, "EXIT=>%s:%s, %d\n\r",__FILE__, __FUNCTION__, __LINE__)
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
#define EXIT_FUNCTION
#define LOG_PRINT
#define LOG_ERR

#endif
#endif

