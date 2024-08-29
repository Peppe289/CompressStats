#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/random.h>
#include <stdlib.h>

#include "va_args.h"
#include "sys_random.h"

#ifndef FILE_NAME
#define FILE_NAME "file"
#endif

#define FULL_MODE_FILE S_IRWXU | S_IRWXG | S_IRWXO
#define RANDOM_BLOCK 1024

static int write_for_1mb(int fd)
{
    int ret;
    int i = 0;
    do
    {
        // write 1 kb at time.
        ret = write(fd, get_random(), RANDOM_BLOCK);
        if (ret < 0)
            __exit_msg_errno(-1, "Error to writing in file stopped at: %d", i);

        ++i;
    } while (i != RANDOM_BLOCK);

    // return all iterator
    return i;
}

static int write_for_1gb(int fd)
{
    int i = 0;
    for (; i != RANDOM_BLOCK; ++i)
    {
        write_for_1mb(fd);
    }
}

int main()
{
    int fd;
    int ret;

    fd = open(FILE_NAME, O_WRONLY | O_CREAT | O_TRUNC, FULL_MODE_FILE);
    if (fd < 0)
        __exit_msg(0, "Error to create file");

    // init module for random byte.
    init_random_data();

    write_for_1gb(fd);

    // make free module for random byte.
    exit_random_data();

    close(fd);

    return 0;
}