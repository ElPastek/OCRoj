## Simple SDL mini code

CC=gcc

CPPFLAGS= `pkg-config --cflags sdl` `pkg-config --cflags gtk+-3.0` 
CFLAGS= -Wall -Wextra -std=c99 
LDFLAGS= -rdynamic
LDLIBS= `pkg-config --libs sdl` -lSDL_image `pkg-config --libs gtk+-3.0`

SRC= window_test.c 
OBJ= ${SRC:.c=.o}

all: CFLAGS += -O3
all: window_test

debug: CFLAGS += -g -O0
debug: window_test

main: ${OBJ}

clean:
	rm -f *~ *.o
	rm -f window_test

# END MDRRR
