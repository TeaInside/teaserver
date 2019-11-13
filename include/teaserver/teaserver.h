
/**
 * TeaServer
 *
 * @author Ammar Faizi <ammarfaizi2@gmail.com> https://www.facebook.com/ammarfaizi2
 * @license MIT
 * @version 0.0.1
 */

#ifndef __teaserver__teaserver_h
#define __teaserver__teaserver_h

#define TEASERVER_VERSION "0.0.1"

#include <time.h>
#include <stdint.h>
#include <stdbool.h>

struct teaserver_http {
    char *bind_addr;
    char *access_log;
    char *config_file;
    uint8_t verbose_level;
    uint16_t bind_port;
    uint8_t threads;
};

union teaserver_uni_type {
    struct teaserver_http http;
};

enum teaserver_type {
    TEASERVER_HTTP = (1 << 0)
};

struct teaserver_arg {
    enum teaserver_type type;
    union teaserver_uni_type config;
};

bool argv_parser(int argc, char **argv, char **envp, struct teaserver_arg *arg);
uint8_t teaserver_http_run(struct teaserver_arg *arg);
void internal_teaserver_debug_log(const char *format, ...);


 __attribute__((always_inline)) inline static char *__internal_get_rawtime()
{
    register char *timestr;
    time_t rawtime;

    time(&rawtime);

    timestr = asctime(localtime(&rawtime));
    timestr[24] = '\0';

    return timestr;
}



#define debug_log(VLEVEL, FORMAT, ...) \
    if (VLEVEL <= verbose_level) { \
        internal_teaserver_debug_log( \
            "[]: "FORMAT"\n", \
            __internal_get_rawtime(), \
            ##__VA_ARGS__ \
        ); \
    }

#endif
