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

enum unit
{
    ERR = -1,
    KB,
    MB,
    GB,
};

struct file_unit
{
    enum unit type;
    ssize_t size;
};

#define for_size(iterator, input_size) for (iterator = 0; iterator < input_size; ++iterator)

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

// change from input args, the type from char to enum.
static enum unit _define_unit(const char lastchar)
{
    enum unit type;

    if (lastchar == 'G' || lastchar == 'g')
        type = GB;
    else if (lastchar == 'M' || lastchar == 'm')
        type = MB;
    else if (lastchar == 'K' || lastchar == 'k')
        type = KB;
    else
        type = ERR;

    return type;
}

static struct file_unit get_args_prop(const char *argv)
{
    struct file_unit unity;
    char type;

    sscanf(argv, "%lu%c", &unity.size, &type);
    unity.type = _define_unit(type);

    return unity;
}

int main(int argc, char *argv[])
{
    int fd;
    struct file_unit prop;
    int i;

    if (argc < 1)
        __exit_msg(0, "Please specify file size like: %s 2G", argv[0]);

    fd = open(FILE_NAME, O_WRONLY | O_CREAT | O_TRUNC, FULL_MODE_FILE);
    if (fd < 0)
        __exit_msg(0, "Error to create file");

    // init module for random byte.
    init_random_data();

    prop = get_args_prop(argv[1]);

    switch (prop.type)
    {
    case GB:
        for_size(i, prop.size)
        {
            write_for_1gb(fd);
        }
        break;
    case MB:
        for_size(i, prop.size)
        {
            write_for_1mb(fd);
        }
        break;
    case KB:
        for_size(i, prop.size)
        {
            write(fd, get_random(), RANDOM_BLOCK);
        }
        break;
    default:
        break;
    }

    // make free module for random byte.
    exit_random_data();

    close(fd);

    return 0;
}