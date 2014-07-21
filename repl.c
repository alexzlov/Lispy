#include <stdio.h>
#include <stdlib.h>
#include <editline/readline.h>

#include "mpc.h"
#include "term_colors.h"

/* Static buffer for user input */
static char input[2048];

void print_version() {
    printf("%s%s", FG_COLOR_WHITE, BG_COLOR_RED);
    puts("Lispy Version 0.0.1 ");
    printf("Press Ctrl+c to Exit\n");
    printf(COLOR_RESET);
}

/* Eval operand */
long eval_op(long x, char* op, long y) {
    if (strcmp(op, "+") == 0) { return x + y; }
    if (strcmp(op, "-") == 0) { return x - y; }
    if (strcmp(op, "*") == 0) { return x * y; }
    if (strcmp(op, "/") == 0) { return x / y; }
    return 0;
}

long eval(mpc_ast_t* t) {
    
    /* If tagged as number return it directly, otherwise expression. */
    if (strstr(t->tag, "number")) { return atoi(t->contents); }

    /* The operator is always second child. */
    char* op = t->children[1]->contents;

    /* We store the third child in `x`. */
    long x = eval(t->children[2]);

    /* Iterate the remaining children, combining using our operator */
    int i = 3;
    while (strstr(t->children[i]->tag, "expr")) {
        x = eval_op(x, op, eval(t->children[i]));
        i++;
    }

    return x;
}

int main(int argc, char** argv) {

    /* Create some parsesr */
    mpc_parser_t* Number          = mpc_new("number");
    mpc_parser_t* Operator        = mpc_new("operator");
    mpc_parser_t* Expr            = mpc_new("expr");
    mpc_parser_t* Lispy           = mpc_new("lispy");

    /* Grammar rules */
    mpca_lang(MPCA_LANG_DEFAULT,
        "                                                             \
          number        : /-?[0-9]+/ ;                                \
          operator      : '+' | '-' | '*' | '/';                      \
          expr          : <number> | '(' <operator> <expr>+ ')';      \
          lispy         : /^/ <operator> <expr>+ /$/;                 \
        ",
        Number, Operator, Expr, Lispy);

    print_version();
    while (1) {
        printf(FG_COLOR_YELLOW);
        printf("repl> ");
        char* input = readline(COLOR_RESET);
        printf(COLOR_RESET);
        add_history(input);

        mpc_result_t r;
        if (mpc_parse("<stdin>", input, Lispy, &r)) {
            /* On success print the AST */
            long result = eval(r.output);
            printf("%s%li%s\n", FG_COLOR_CYAN, result, COLOR_RESET);
            mpc_ast_delete(r.output);
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

    mpc_cleanup(4, Number, Operator, Expr, Lispy);
    return 0;
}
