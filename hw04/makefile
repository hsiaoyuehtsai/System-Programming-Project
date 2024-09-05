SHELL = /bin/bash
CC = gcc
CFLAGS = -lrt -g -pthread -z lazy
SRC = $(wildcard *.c)
EXE = $(patsubst %.c, %, $(SRC))

all: ${EXE}

%:	%.
	${CC} ${CFLAGS} $@.c -o $@
	sudo chown root $@
	sudo chmod +s $@

clean:
	rm ${EXE}
