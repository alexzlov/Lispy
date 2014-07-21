#include <stdio.h>
#include <stdlib.h>

#include <editline/readline.h>

/* Static buffer for user input */
static char input[2048];

int main(int argc, char** argv) {
    
    puts("Lispy Version 0.0.1");
    puts("Press Ctrl+c to Exit\n");

    while (1) {
        char* input = readline("repl> ");
        add_history(input);
        printf("Got it: %s\n", input);
        free(input);
    }

    return 0;
}
