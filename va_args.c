
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>

#include "va_args.h"

static void sys_print(int out_fd, const char *string)
{
    write(out_fd, string, strlen(string) + 1);
}

// from man vprintf(2)
static char *
make_message(const char *fmt, ...)
{
    int n = 0;
    size_t size = 0;
    char *p = NULL;
    va_list ap;

    /* Determine required size. */

    va_start(ap, fmt);
    n = vsnprintf(p, size, fmt, ap);
    va_end(ap);

    if (n < 0)
        return NULL;

    size = (size_t)n + 1; /* One extra byte for '\0' */
    p = malloc(size);
    if (p == NULL)
        return NULL;

    va_start(ap, fmt);
    n = vsnprintf(p, size, fmt, ap);
    va_end(ap);

    if (n < 0)
    {
        free(p);
        return NULL;
    }

    return p;
}


/**************** module API function ****************/

void sys_print_out(const char *string)
{
    sys_print(STDOUT_FILENO, string);
}

void sys_print_err(const char *string)
{
    sys_print(STDERR_FILENO, string);
}

void __exit_msg_errno(const int err, const char *fmt, ...)
{
    va_list ap;
    char *msg;
    char buf[1024];

    // make as first instruction after alloc stack.
    sprintf(buf, ": %s (%d)", strerror(errno), errno);

    va_start(ap, fmt);
    msg = make_message(fmt, ap);
    va_end(ap);

    if (!msg)
    {
        // some error happned if we not able to retrieve va_args.
        sys_print(STDERR_FILENO, "Critical error: unable to printing.");
        exit(-1);
    }

    msg = strcat(msg, buf);
    sys_print(STDOUT_FILENO, msg);
    exit(err);
}


void __exit_msg(const int err, const char *fmt, ...)
{
    va_list ap;
    char *msg;

    va_start(ap, fmt);
    msg = make_message(fmt, ap);
    va_end(ap);

    if (!msg)
    {
        // some error happned if we not able to retrieve va_args.
        sys_print(STDERR_FILENO, "Critical error: unable to printing.");
        exit(-1);
    }

    sys_print(STDOUT_FILENO, msg);
    exit(err);
}