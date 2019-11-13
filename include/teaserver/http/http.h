
/**
 * TeaServer
 *
 * @author Ammar Faizi <ammarfaizi2@gmail.com> https://www.facebook.com/ammarfaizi2
 * @license MIT
 * @version 0.0.1
 */

#ifndef __teaserver__http_http_h
#define __teaserver__http_http_h

#include <stdio.h>
#include <teaserver/teaserver.h>

typedef struct _teaserver_http_access_log {
    FILE *handle;
    char *filename;
} teaserver_http_access_log;

bool teaserver_http_config_parser(struct teaserver_arg *arg);

extern int8_t verbose_level;

#endif
