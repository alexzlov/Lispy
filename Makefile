CC=cc
CFLAGS=-std=c99 -Wall
SOURCES=repl.c mpc.c
LDFLAGS=-ledit -lm
EXECUTABLE=repl

all:
	$(CC) $(SOURCES) $(LDFLAGS) -o repl

clean:
	rm -f repl
	rm -f *.out
	rm -f *.o
