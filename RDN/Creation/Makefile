# Simple Makefile
 
# Compilers vars
CC=gcc
CPPFLAGS= -MMD 
CFLAGS= -Wall -Wextra -pedantic -std=c99 -O2
LDFLAGS=
LDLIBS= -lm

SRC= RDN_main_2.c
DEP= ${SRC:.c=.d}
PRG= ${SRC:.c=}
 
all: ${PRG}
 
-include ${DEP}
 
clean:
	rm -f *.o
	rm -f ${DEP}
	rm -f ${PRG}
	rm -f *.out
# END Makefile
