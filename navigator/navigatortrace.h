#ifndef _NAVIGATORTRACE_H_
#define _NAVIGATORTRACE_H_

#include "logging.h"

#define LOGGING_TRACE_RECT(msg, rc) \
    logging_trace("%s: RECT(left = %d, top = %d, right = %d, bottom = %d)\r\n", \
        msg, rc->left, rc->top, rc->right, rc->bottom)

#endif

