# Simple Makefile
# -O2

CC=gcc
CFLAGS= -Wall -Wextra -pedantic -std=c99 -I./network
LDLIBS= -lm

SRC= Creation/RDN_main.c
PRG= ${SRC:.c=}
DIR= Lecture/lecture.c
LEC= ${DIR:.c=}

all: ${PRG}

train: ${PRG}

read: ${LEC}

clean:
	rm -f ${PRG}
# END Makefile
