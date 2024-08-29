#ifndef __PRIV_SYS_RANDOM_H_
#define __PRIV_SYS_RANDOM_H_

#define RANDOM_BLOCK 1024

char *get_random();
void init_random_data();
void exit_random_data();

#endif