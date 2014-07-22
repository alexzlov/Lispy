#ifndef LVAL_H_
#define LVAL_H_
enum {
    LVAL_NUM,       // Number value
    LVAL_ERR,       // Error value
    LVAL_SYM,       // Symbol
    LVAL_SEXPR      // S-expression
};

/* lval can be a number or an error */
typedef struct lval {
    int     type;

    long    num;

    /* Error and Symbol types have some string data */
    char*   err;
    char*   sym;

    /* Count and Pointer to a list of "lval*" */
    int     count;
    struct  lval** cell;

} lval;

/* Construct a pointer to a new Number lval */
lval* lval_num(long x);

/* Construct a pointer to a new Error lval */
lval* lval_err(char* m);

/* Construct a pointer to a new Symbol lval */
lval* lval_sym(char* s);

/* A pointer to a new empty Sexpr lval */
lval* lval_sexpr(void);

/* Destructor */
void lval_del(lval* v);

/* Add an element to S-expression */
lval* lval_add(lval* v, lval* x);

lval* lval_read_num(mpc_ast_t* t);

lval* lval_read(mpc_ast_t* t);

/* Print out S-expression */
void lval_expr_print(lval* v, char open, char close);
void lval_print(lval* v);
void lval_println(lval* v);

#endif
