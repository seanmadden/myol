#include <stdio.h>

typedef struct {
    int type;
    long num;
    int err;
} lval;

enum {
    LVAL_NUM,
    LVAL_ERR
};

enum {
    LERR_DIV_ZERO,
    LERR_BAD_OP,
    LERR_BAD_NUM
};

lval lval_num(long number);
lval lval_err(int errorId);
void lval_print(lval val);
void lval_println(lval val);
