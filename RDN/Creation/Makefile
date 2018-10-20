# Simple Makefile
# -O2

CC=gcc
CFLAGS= -Wall -Wextra -pedantic -std=c99 -g -I.. 
#-fsanitize=address
LDLIBS= -lm

SRC= RDN_main.c
PRG= ${SRC:.c=}

all: ${PRG}

clean:
	rm -f ${PRG}
# END Makefile
