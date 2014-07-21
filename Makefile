CC=cc
CFLAGS=-std=c99 -Wall
SOURCES=repl.c mpc.c lval.c
LDFLAGS=-ledit
EXECUTABLE=repl

all:
	$(CC) $(SOURCES) $(LDFLAGS) -o repl

clean:
	rm -f repl
	rm -f *.out
	rm -f *.o
