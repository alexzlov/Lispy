#include <stdio.h>

/* Static buffer for user input */
static char input[2048];

int main(int argc, char** argv) {
    
    puts("Lispy Version 0.0.1");
    puts("Press Ctrl+c to Exit\n");

    while (1) {
        fputs("repl> ", stdout);
        fgets(input, 2048, stdin);
        printf("Got it: %s", input);
    }

    return 0;
}
