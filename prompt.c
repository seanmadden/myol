#include <stdio.h>
#include <stdlib.h>

#include <editline/readline.h>
#include "dependencies/mpc.h"

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
            mpc_ast_print(result.output);
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
