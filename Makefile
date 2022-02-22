CC=gcc
CFLAGS=-Wall -g

%: %.c
	${CC} ${CFLAGS} $@.c -o $@.o

clean:
	rm -rf *.o
