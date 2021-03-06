#include <stdio.h>
#include <stdlib.h>

#include <editline/readline.h>
#include "dependencies/mpc.h"
#include "lval_core.h"

lval eval(mpc_ast_t* node);
lval eval_op(lval x, char* op, lval y);

lval eval(mpc_ast_t* node) {
    //base case: number
    if (strstr(node->tag, "number")) {
        errno = 0;
        long x = strtol(node->contents, NULL, 10);
        return errno != ERANGE ? lval_num(x) : lval_err(LERR_BAD_NUM);
    }

    //operator is always the second child
    char* operator = node->children[1]->contents;

    //third child
    lval x = eval(node->children[2]);

    int i = 3;
    //Loop over the remaining expressions
    while (strstr(node->children[i]->tag, "expr")) {
        x = eval_op(x, operator, eval(node->children[i]));
        i++;
    }

    return x;
}

/*
 * Check operator string to see which operation to perform 
 */
lval eval_op(lval x, char* op, lval y) {
    if (x.type == LVAL_ERR) { return x; }
    if (y.type == LVAL_ERR) { return y; }

    if (strcmp(op, "+") == 0) { return lval_num(x.num + y.num); }
    if (strcmp(op, "-") == 0) { return lval_num(x.num - y.num); }
    if (strcmp(op, "*") == 0) { return lval_num(x.num * y.num); }
    if (strcmp(op, "/") == 0) { 
        return y.num == 0 ? lval_err(LERR_DIV_ZERO) : lval_num(x.num / y.num);
    }
    
    return lval_err(LERR_BAD_OP);
}

int main(int argc, char** argv) {
    
    //Let's define the grammar 
    mpc_parser_t* Number        = mpc_new("number");
    mpc_parser_t* Operator      = mpc_new("operator");
    mpc_parser_t* Expr          = mpc_new("expr");
    mpc_parser_t* Lispy         = mpc_new("lispy");

    mpca_lang(MPCA_LANG_DEFAULT,
    "                                                           \
        number      :   /-?[0-9]+/ ;                            \
        operator    :   '+' | '-' | '/' | '*' ;                 \
        expr        :   <number> | '(' <operator> <expr>+ ')' ; \
        lispy       :   /^/ <operator> <expr>+ /$/ ;            \
    ",
    Number, Operator, Expr, Lispy);


    //Print latest version
    puts("Lispy Version 0.0.0.1");
    puts("Press Ctrl-c to exit\n");

    while (1) {
        char* input = readline("lispy> ");
        add_history(input);

        mpc_result_t result;
        if (mpc_parse("<stdin>", input, Lispy, &result)) {
            lval value = eval(result.output);
            lval_println(value);
            mpc_ast_delete(result.output);
        } else {
            //Parsing error
            mpc_err_print(result.error);
            mpc_err_delete(result.error);
        }

        free(input);
    }

    return 0;
}
