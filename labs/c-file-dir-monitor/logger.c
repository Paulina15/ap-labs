#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include <syslog.h>
#include "logger.h"

int isSyslog = 0;

int initLogger(char *logType) {
    printf("Initializing Logger on: %s\n", logType);
     if (strcmp(logType, "syslog") == 0){
        isSyslog = 1;
    } 
    else if (strcmp(logType, "stdout") == 0 || strlen(logType) == 0){
        isSyslog = 0;
    }
    else {
        printf("Invalid arguments");
    }
    return 0;
}

int infof(const char *format, ...) {
    va_list arg;
    va_start(arg, format);
     if (isSyslog == 1){
        vsyslog(LOG_INFO, format, arg);
        closelog();
    }
    else if (isSyslog == 0){
        vprintf(format, arg);

    }
    va_end(arg);
    printf("\n");
    return 0;
}

int warnf(const char *format, ...) {
    va_list arg;
    va_start(arg, format);
    if (isSyslog == 1){
        vsyslog(LOG_INFO, format, arg);
        closelog();
    }
    else if (isSyslog == 0){
        vprintf(format, arg);

    }
    va_end(arg);
    printf("\n");
    return 0;
}

int errorf(const char *format, ...) {
    va_list arg;
    va_start(arg, format);
    if (isSyslog == 1){
        vsyslog(LOG_INFO, format, arg);
        closelog();
    }
    else if (isSyslog == 0){
        vprintf(format, arg);

    }
    va_end(arg);
    printf("\n");
    return 0;
}
int panicf(const char *format, ...) {
     va_list arg;
    va_start(arg, format);
    if (isSyslog == 1){
        vsyslog(LOG_INFO, format, arg);
        closelog();
    }
    else if (isSyslog == 0){
        vprintf(format, arg);

    }
    va_end(arg);
    printf("\n");
    return 0;
}

