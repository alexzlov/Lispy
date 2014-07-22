#include <stdio.h>
#include <stdlib.h>
#include <editline/readline.h>

#include "mpc.h"
#include "term_colors.h"
#include "lval.h"

/* Static buffer for user input */
static char input[2048];

void print_version() {
    printf("%s%s", FG_COLOR_WHITE, BG_COLOR_RED);
    printf("Lispy Version 0.0.1 \n");
    printf("Press Ctrl+c to Exit\n");
    printf("%s%s\n", BG_COLOR_BLACK, COLOR_RESET);
}

int main(int argc, char** argv) {

    /* Create some parsesr */
    mpc_parser_t* Number          = mpc_new("number");
    mpc_parser_t* Symbol          = mpc_new("symbol");
    mpc_parser_t* Sexpr           = mpc_new("sexpr");
    mpc_parser_t* Expr            = mpc_new("expr");
    mpc_parser_t* Lispy           = mpc_new("lispy");

    /* Grammar rules */
    mpca_lang(MPCA_LANG_DEFAULT,
        "                                                             \
          number        : /-?[0-9]+/ ;                                \
          symbol        : '+' | '-' | '*' | '/' | '%';                \
          sexpr         : '(' <expr>* ')';                            \
          expr          : <number> | <symbol> | <sexpr>;              \
          lispy         : /^/ <expr>* /$/;                            \
        ",
        Number, Symbol, Sexpr, Expr, Lispy);

    print_version();
    while (1) {
        printf(FG_COLOR_YELLOW);
        printf("repl> ");
        char* input = readline(COLOR_RESET);
        printf(COLOR_RESET);
        add_history(input);

        mpc_result_t r;
        if (mpc_parse("<stdin>", input, Lispy, &r)) {
            /* On success eval and print the AST */
            /*lval result = eval(r.output);*/
            /*lval_println(result);*/
            lval* x = lval_read(r.output);
            printf(FG_COLOR_MAGENTA);
            lval_println(x);
            printf(COLOR_RESET);
            lval_del(x);
            /*mpc_ast_print(r.output);*/
            mpc_ast_delete(r.output);
            printf(COLOR_RESET);
        } else {
            /* Otherwise print the error */
            printf(FG_COLOR_RED);
            mpc_err_print(r.error);
            mpc_err_delete(r.error);
            printf(COLOR_RESET);
        }

        free(input);
    }
    printf(COLOR_RESET);

    mpc_cleanup(5, Number, Symbol, Sexpr, Expr, Lispy);
    return 0;
}
