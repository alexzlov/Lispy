#include <stdio.h>
#include <stdlib.h>
#include <editline/readline.h>

#include "term_colors.h"

/* Static buffer for user input */
static char input[2048];

int main(int argc, char** argv) {
    printf(FG_COLOR_WHITE);
    puts("Lispy Version 0.0.1");
    puts("Press Ctrl+c to Exit\n");
    printf(COLOR_RESET);

    while (1) {
        printf(FG_COLOR_YELLOW);
        printf("repl> ");
        char* input = readline(COLOR_RESET);
        printf(COLOR_RESET);
        add_history(input);
        printf("Got it: %s\n", input);
        free(input);
    }
    printf(COLOR_RESET);

    return 0;
}
