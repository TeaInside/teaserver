
/**
 * TeaServer
 *
 * @author Ammar Faizi <ammarfaizi2@gmail.com> https://www.facebook.com/ammarfaizi2
 * @license MIT
 * @version 0.0.1
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#include <unistd.h>
#include <teaserver/teaserver.h>

static const struct option http_options[] = {
    {"bind-addr",   required_argument, 0, 'S'},
    {"bind_addr",   required_argument, 0, 'S'},
    {"bind-port",   required_argument, 0, 'p'},
    {"bind_port",   required_argument, 0, 'p'},
    {"access-log",  required_argument, 0, 'a'},
    {"access_log",  required_argument, 0, 'a'},
    {"config-file", required_argument, 0, 'c'},
    {"config_file", required_argument, 0, 'c'},
    {"threads",     required_argument, 0, 't'},
    {"version",     required_argument, 0, 0x1},
    {"verbose",     no_argument,       0, 'v'},
    {"help",        no_argument,       0, 'h'},
    {0, 0, 0, 0}
};

enum cmd_list {
    TEASERVER_CMD_HTTP = (1 << 0)
};

static void show_general_help(char *appname);
static void show_cmd_help(char *appname, enum cmd_list cmd);
static bool arg_http_parser(char *appname, int argc, char **argv, char **envp, struct teaserver_arg *arg);

/**
 * Parse command line arguments.
 *
 * @param int                       argc
 * @param char                      **argv
 * @param char                      **envp
 * @param struct teaserver_arg      *arg
 * @return bool
 */
bool argv_parser(int argc, char **argv, char **envp, struct teaserver_arg *arg)
{
    if (argc == 1) {
        show_general_help(argv[0]);
        return false;
    }


    if ((!strcmp(argv[1], "version")) || (!strcmp(argv[1], "--version"))) {
        printf("Tea Server %s\n", TEASERVER_VERSION);
        return false;
    } else if (!strcmp(argv[1], "http")) {
        return arg_http_parser(argv[0], argc - 1, &(argv[1]), envp, arg);
    } else if ((!strcmp(argv[1], "help")) || (!strcmp(argv[1], "--help"))) {
        show_general_help(argv[0]);
        return false;
    }

    printf("Unknown command \"%s\"\n", argv[1]);
    return false;
}



/**
 * Show general help.
 *
 * @param char      *appname
 * @return void
 */
static void show_general_help(char *appname)
{
    #define COMMAND_X(A, B) "\t" A "\t\t" B "\n"

    printf(
        "Usage: %s [command] [options]\n\n"
        "Available commands:\n"
        COMMAND_X("http",       "Run HTTP server.")
        COMMAND_X("version",    "Show application version"),
        appname
    );

    #undef COMMAND_X
}



/**
 * Show help for specific command.
 *
 * @param char              *appname
 * @param enum cmd_list     cmd
 * @return void
 */
static void show_cmd_help(char *appname, enum cmd_list cmd)
{
    #define OPT_X(A, B) "\t" A "\t\t" B "\n"

    switch (cmd) {
        case TEASERVER_CMD_HTTP:
            printf(
                "Usage: %s http [options]\n\n"
                "Available options:\n"
                OPT_X("--config|-c\t<file>\t", "Use config file.")
                OPT_X("--bind-addr|-S\t<address>", "Specify bind address.")
                OPT_X("--bind-port|-p\t<port>\t", "Specify bind port.")
                OPT_X("--access-log|-a\t<file>\t", "Write access log to file.") "\n"
                OPT_X("--verbose|-v\t\t", "Run verbose mode. (Use -vvv to increase verbose level)."),
                appname
            );
            break;
        default:
            break;
    }

    #undef OPT_X
}



/**
 * Parse argument for http command.
 *
 * @param char                      *appname
 * @param int                       argc
 * @param char                      **argv
 * @param char                      **envp
 * @param struct teaserver_arg      *arg
 * @return bool
 */
static bool arg_http_parser(char *appname, int argc, char **argv, char **envp, struct teaserver_arg *arg)
{
    int c, option_index;

    arg->type = TEASERVER_HTTP;
    arg->config.http.bind_addr = NULL;
    arg->config.http.bind_port = 0;
    arg->config.http.access_log = NULL;
    arg->config.http.threads = 0;
    arg->config.http.config_file = NULL;
    arg->config.http.verbose_level = 0;

    while (true) {

        option_index = 0;
        c = getopt_long(argc, argv, "S:p:c:va:t:", http_options, &option_index);
        if (c == -1) break;

        switch (c) {

            case 'a':
                arg->config.http.access_log = optarg;
                break;

            case 'h':
                show_cmd_help(appname, TEASERVER_CMD_HTTP);
                return false;
                break;

            case 'S':
                arg->config.http.bind_addr = optarg;
                break;

            case 'p':
                arg->config.http.bind_port = (uint16_t)atoi(optarg);
                break;

            case 'c':
                arg->config.http.config_file = optarg;
                break;

            case 'v':
                arg->config.http.verbose_level++;
                break;

            case 't':
                arg->config.http.threads = (uint8_t)atoi(optarg);
                break;

            default:
                return false;
                break;
        }
    }

    /**
     * Debug http config which is formed from cli arguments.
     */

    #ifdef TEA_SERVER_DEBUG
    printf(
        "arg->type = %s\n"
        "arg->config.http.bind_addr = %s\n"
        "arg->config.http.bind_port = %d\n"
        "arg->config.http.access_log = %s\n"
        "arg->config.http.threads = %d\n"
        "arg->config.http.config_file = %s\n"
        "arg->config.http.verbose_level = %d\n",
        (
            arg->type == TEASERVER_HTTP ? "TEASERVER_HTTP" : "Unknown"
        ),
        arg->config.http.bind_addr,
        arg->config.http.bind_port,
        arg->config.http.access_log,
        arg->config.http.threads,
        arg->config.http.config_file,
        arg->config.http.verbose_level
    );
    fflush(stdout);
    #endif

    return true;
}
