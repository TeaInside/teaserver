
/**
 * TeaServer
 *
 * @author Ammar Faizi <ammarfaizi2@gmail.com> https://www.facebook.com/ammarfaizi2
 * @license MIT
 * @version 0.0.1
 */

#include <stdio.h>
#include <stdarg.h>
#include <teaserver/teaserver.h>

int8_t verbose_level;

/**
 * Print debug log.
 *
 * It will be called by macro debug_log.
 */
void internal_teaserver_debug_log(const char *format, ...)
{
	va_list argp;

	va_start(argp, format);
	vfprintf(stdout, format, argp);
	va_end(argp);
	fflush(stdout);
}
