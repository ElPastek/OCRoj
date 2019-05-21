# Simple Makefile


CC=gcc
CFLAGS= -Wall -Wextra -pedantic -std=c99 -g
LDLIBS= -lm

SRC= lecture.c
PRG= ${SRC:.c=}

all: ${PRG}

-include ${DEP}

clean:
	rm -f ${DEP}
# END Makefile
