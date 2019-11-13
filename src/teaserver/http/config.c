
/**
 * TeaServer
 *
 * @author Ammar Faizi <ammarfaizi2@gmail.com> https://www.facebook.com/ammarfaizi2
 * @license MIT
 * @version 0.0.1
 */

#include <stdlib.h>
#include <string.h>

#include <teaserver/teaserver.h>
#include <teaserver/http/http.h>

#include <third_party/inih/ini.h>


static int handler(void* user, const char* section, const char* name, 
                    const char* value);


/**
 * Parse ini file.
 */
bool teaserver_http_config_parser(struct teaserver_arg *arg)
{
    if (ini_parse(arg->config.http.config_file, handler, arg) < 0) {
        debug_log(0, "Error: Cannot load \"%s\"", arg->config.http.config_file);
        return false;
    }

    return true;
}

/**
 * Parser handler.
 */
static int handler(void* user, const char* section, const char* name,
                   const char* value)
{
    #define arg ((struct teaserver_arg *)user)


    if (!strcmp(section, "http")) {
        if (!strcmp(name, "bind_addr")) {
            arg->config.http.bind_addr = strdup(value);
        } else if (!strcmp(name, "bind_port")) {
            arg->config.http.bind_port = (uint16_t)atoi(value);
        } else if (!strcmp(name, "threads")) {
            arg->config.http.threads = (uint8_t)atoi(value);
        }

        printf("%s %s %s\n", section, name, value);
    }

    return 1;

    #undef arg
}
