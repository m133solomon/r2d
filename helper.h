#ifndef HELPER_H
#define HELPER_H

#include <stdlib.h>
#include <stdarg.h>

void LOG_ERROR(char *fmt, ...)
{
    va_list argp;
    fprintf(stderr, "error: ");
    va_start(argp, fmt);
    vfprintf(stderr, fmt, argp);
    va_end(argp);
    fprintf(stderr, "\n");
}


#endif // HELPER_H
