#include "lval_core.h"

lval lval_num(long number) {
    lval val;
    val.type = LVAL_NUM;
    val.num = number;

    return val;
}

lval lval_err(int error) {
    lval val;
    val.type = LVAL_ERR;
    val.err = error;

    return val;
}

void lval_print(lval val) {
    switch (val.type) {
        case LVAL_NUM:
            printf("%li", val.num);
            break;
        case LVAL_ERR:
            if (val.err == LERR_DIV_ZERO) {
                printf("ERROR: Divizion by zero!");
            }
            if (val.err == LERR_BAD_OP) { 
                printf("ERROR: Invalid operator!");
            }
            if (val.err == LERR_BAD_NUM) { 
                printf("ERROR: Invalid number!");
            }
            break;
    }
};

void lval_println(lval val) {
    lval_print(val);
    putchar('\n');
}
