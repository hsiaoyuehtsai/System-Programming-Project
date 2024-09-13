SHELL = /bin/bash
CC = gcc
CFLAGS = -g 
SRC = $(wildcard *.c)
EXE = $(patsubst %.c, %, $(SRC))

all: ${EXE}

%:	%.
	${CC} ${CFLAGS} $@.c -o $@

clean:
	rm ${EXE}
