#ifndef __PRIV_VA_ARGS_H_
#define __PRIV_VA_ARGS_H_



/* exit from program printing fmt concat errno code and return to system err code. */
void __exit_msg_errno(const int err, const char *fmt, ...);
void __exit_msg(const int err, const char *fmt, ...); // same but without errno code.


/* output without buffer */
void sys_print_out(const char *string);
void sys_print_err(const char *string);


#endif