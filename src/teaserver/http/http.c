
/**
 * TeaServer
 *
 * @author Ammar Faizi <ammarfaizi2@gmail.com> https://www.facebook.com/ammarfaizi2
 * @license MIT
 * @version 0.0.1
 */

#include <stdio.h>
#include <stdlib.h>

#include <teaserver/http/http.h>

static char default_bind_addr[] = "0.0.0.0";
static bool teaserver_http_init(struct teaserver_arg *arg);

/**
 * Main point of HTTP server.
 */
uint8_t teaserver_http_run(struct teaserver_arg *arg)
{
    if (!teaserver_http_init(arg)) {
        return 1;
    }

    return 1;
}



/**
 * Initialize HTTP Server.
 */
static bool teaserver_http_init(struct teaserver_arg *arg)
{

    verbose_level = arg->config.http.verbose_level;

    if (arg->config.http.bind_addr == NULL) {
        arg->config.http.bind_addr = default_bind_addr;
        debug_log(3, "Notice: Bind address is empty, auto set to 0.0.0.0");
    }

    if (arg->config.http.bind_port == 0) {
        arg->config.http.bind_port = 8000;
        debug_log(3, "Notice: Bind port is empty, auto set to 8000");
    }

    if (arg->config.http.threads == 0) {
        debug_log(1, "Warning: Threads number cannot be zero,"
            "auto set to 1");
        arg->config.http.threads = 1;
    }

    if (arg->config.http.config_file != NULL) {
        if (!teaserver_http_config_parser(arg)) {
            return false;
        }
    }

    return true;
}
