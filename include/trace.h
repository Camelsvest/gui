#ifndef _TRACE_H_
#define _TRACE_H_

#include "logging.h"

#ifdef __WIN32_WINNT
    #define FILENAME(x) (strrchr(x,'\\')?strrchr(x,'\\')+1:x)
#else
    #define FILENAME(x) (strrchr(x,'/')?strrchr(x,'/')+1:x)
#endif

#define __FILENAME__     (FILENAME(__FILE__))

#define ENTER_CLASS_FUNCTION(class_name) logging_verbos("Enter %s->%s, %s:%u\r\n", class_name, __FUNCTION__, __FILENAME__, __LINE__)
#define EXIT_CLASS_FUNCTION(class_name)  logging_verbos("Exit %s->%s, %s:%u\r\n", class_name, __FUNCTION__, __FILENAME__, __LINE__);

#define ENTER_FUNCTION  logging_verbos("Enter %s, %s:%u\r\n", __FUNCTION__, __FILENAME__, __LINE__)
#define EXIT_FUNCTION   logging_verbos("Exit %s, %s:%u\r\n", __FUNCTION__, __FILENAME__, __LINE__);


#endif
