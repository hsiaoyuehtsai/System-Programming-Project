SHELL = /bin/bash
CC = gcc
CFLAGS = -g -pthread
SRC = $(wildcard *.c)
EXE = $(patsubst %.c, %, $(SRC))

all: ${EXE}
	echo 3500 > lockf.db
	echo 3500 > flock.db
%:	%.c
	${CC} ${CFLAGS} $@.c -o $@


	
clean:
	rm ${EXE}
	rm -f flock.db
	rm -f lockf.db