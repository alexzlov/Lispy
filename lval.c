#include "lval.h"
#include <stdio.h>
#include "term_colors.h"

/* Create a new number type lval */
lval lval_num(long x) {
    lval v;
    v.type = LVAL_NUM;
    v.num = x;
    return v;
}

/* Create a new error type lval */
lval lval_err(int x) {
    lval v;
    v.type = LVAL_ERR;
    v.err = x;
    return v;
}

/* Print lval-value */
void lval_print(lval v) {
    switch(v.type) {
        case LVAL_NUM:
            printf(FG_COLOR_CYAN);
            printf("%li", v.num);
            break;
        case LVAL_ERR:
            printf(FG_COLOR_RED);
            switch(v.err) {
                case LERR_DIV_ZERO:
                    printf("Error: division by zero!");
                    break;
                case LERR_BAD_OP:
                    printf("Error: bad operator!");
                    break;
                case LERR_BAD_NUM:
                    printf("Error: bad number!");
                    break;
                default:
                    printf("Unknown error!");
                    break;
            }
    }
    printf(COLOR_RESET);
}

/* Print lval followed by a newline */
void lval_println(lval v) {
    printf(FG_COLOR_CYAN);
    lval_print(v);
    printf(COLOR_RESET);
    putchar('\n');
}
