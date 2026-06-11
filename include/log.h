// log.h
#ifndef LOG_H
#define LOG_H

#include <stdio.h>
#include <time.h>

extern FILE *log_file;

#define LOG(fmt, ...) do { \
    if (log_file) { \
        time_t t = time(NULL); \
        struct tm *tm = localtime(&t); \
        fprintf(log_file, "[%02d:%02d:%02d] " fmt "\n", \
            tm->tm_hour, tm->tm_min, tm->tm_sec, ##__VA_ARGS__); \
        fflush(log_file); \
    } \
} while(0)

#define LOG_OPEN(path) (log_file = fopen(path, "a"))
#define LOG_CLOSE()    do { if (log_file) fclose(log_file); } while(0)

#endif