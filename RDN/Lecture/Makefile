# Simple Makefile


CC=gcc
CFLAGS= -Wall -Wextra -pedantic -std=c99 -g -fsanitize=address
LDLIBS= -lasan -lm

SRC= lecture.c
PRG= ${SRC:.c=}

all: ${PRG}

-include ${DEP}

clean:
	rm -f ${DEP}
# END Makefile
