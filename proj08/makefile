SHELL = /bin/bash
CC = gcc
CFLAGS = -g
LDFLAGS = -lcrypt
SRC = $(wildcard *.c)
EXE = $(patsubst %.c, %, $(SRC))

all: ${EXE}

%: %.c
	${CC} ${CFLAGS} $< -o $@ ${LDFLAGS}

clean:
	rm -f ${EXE}
