/**
 * @file app.c
 * @author Denys Stovbun (denis.stovbun@lanars.com)
 * @brief Defigo d-bus monitor
 *
 * @version 0.1
 * @date 2023-06-26
 */
#define _GNU_SOURCE  /* for vasprintf in stdio.h */
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>
#include <syslog.h>
#include <getopt.h>

#include "app.h"
#include "app_bus.h"


int logLevel = LOG_LEVEL_INFO;
/**
 * @brief Application cmd-line long options list
 */
const struct option long_options[] = {
    {"help",    no_argument,        0,  'h'}, /** show app help and exit */
    {"verbose", no_argument,        0,  'v'}, /** Log-level = debug */
    {"quiet",   no_argument,        0,  'q'}, /** Log-level = error */
    {0,         0,                  0,  0}
};


/**
 * @brief Logging main body
 *
 * @param file current file
 * @param line current line
 * @param func current function
 * @param fmt log format
 * @param argp log other arguments
 */
void selfLogFunction(const char *file, int line, const char *func, int lvl, const char* fmt, ...) {
    size_t sz;
    int r;
    char *msg = NULL;
    struct timeval tv = {0};
    struct tm t = {0};
    char buf[30] = {0};

    if(lvl <= logLevel) {
        gettimeofday(&tv, NULL);
        localtime_r(&tv.tv_sec, &t);
        sz = strftime(buf, sizeof(buf), "%F %T", &t); // %F => %Y-%m-%d,  %T => %H:%M:%S
        snprintf(buf + sz, 30 - sz, ".%03ld", tv.tv_usec / 1000);

        va_list arglist;
        va_start(arglist, fmt);
        r = vasprintf(&msg, fmt, arglist);
        va_end(arglist);
        (void)r;

        printf("%s %s\n", buf, msg);
        fflush(stdout);

        free(msg);
    }

}


/**
 * @brief Main application entrypoint
 *
 * @param argc Arguments count
 * @param argv Arguments values
 * @return int Exit code
 */
int main(int argc, char *argv[]) {
    int r, optIdx, opt;
    selfLogInf("Defigo monitor v.%d.%d.%d", VERSION_MAJOR, VERSION_MINOR, VERSION_REV);

    /** Process command line */
    while ((opt = getopt_long(argc, argv, "hvq", long_options, &optIdx)) != -1) {
        switch(opt) {

            case 'v':
                logLevel = LOG_LEVEL_DEBUG;
                break;

            case 'q':
                logLevel = LOG_LEVEL_ERROR;
                break;

            default: // and '-h'
                printf("Usage: %s [-v|-q]\n-v - verbose mode\n-q - quiet mode\n\n", argv[0]);
                return 0;
        }
    }

    r = bus_init();
    if( r < 0) return -r;

    r = bus_run();

    return abs(r);
}