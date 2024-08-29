#include <sys/random.h>
#include <stdlib.h>

#include "sys_random.h"

static char *rdata;

static ssize_t sys_random()
{
    /* from man page use flag = GRND_RANDOM for read from random source (is more random). */
    return getrandom(rdata, RANDOM_BLOCK, GRND_RANDOM);
}

char *get_random()
{
    sys_random();
    return rdata;
}

void init_random_data()
{
    // this size is 1 byte * 1024 = 1 kb.
    rdata = malloc(sizeof(char) * RANDOM_BLOCK);
    sys_random(rdata);
}

void exit_random_data()
{
    free(rdata);
}