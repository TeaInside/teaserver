
/**
 * TeaServer
 *
 * @author Ammar Faizi <ammarfaizi2@gmail.com> https://www.facebook.com/ammarfaizi2
 * @license MIT
 * @version 0.0.1
 */

#include <stdio.h>
#include <teaserver/teaserver.h>

int main(int argc, char **args, char **envp)
{
    uint8_t exit_code = 0;
    struct teaserver_arg arg;

    if (!argv_parser(argc, args, envp, &arg)) {
        exit_code = 1;
        goto exit_main;
    }

    switch (arg.type) {
        case TEASERVER_HTTP:
            exit_code = teaserver_http_run(&arg);
            break;
        default:
            exit_code = 1;
            printf("Unknown server type: %d\n", arg.type);
            break;
    }

    exit_main:
    return exit_code;
}
