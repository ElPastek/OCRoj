## Simple SDL mini code

CC=gcc

CPPFLAGS= `pkg-config --cflags sdl` `pkg-config --cflags gtk+-3.0` 
CFLAGS= -Wall -Wextra -std=c99 
LDFLAGS= -rdynamic
LDLIBS= `pkg-config --libs sdl` -lSDL_image `pkg-config --libs gtk+-3.0`

SRC= main.c
OBJ= ${SRC:.c=.o}

all: CFLAGS += -O3
all: main

debug: CFLAGS += -g -O0
debug: main

main: ${OBJ}

clean:
	rm -f *~ *.o
	rm -f main

# END MDRRR
