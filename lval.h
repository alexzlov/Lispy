#ifndef LVAL_H_
#define LVAL_H_
enum {
    LVAL_NUM,       // Number value
    LVAL_ERR        // Error value
};

/* Error types */
enum {
    LERR_DIV_ZERO,  // Division by zero error
    LERR_BAD_OP,    // Bad operator error
    LERR_BAD_NUM,   // Bad number error
};

/* lval can be a number or an error */
typedef struct {
    int   type;
    long  num;
    int   err;
} lval;

/* Create a new number type lval */
lval lval_num(long x);

/* Create a new error type lval */
lval lval_err(int x);

/* Print lval-value */
void lval_print(lval v);

/* Print lval followed by a newline */
void lval_println(lval v);

#endif
