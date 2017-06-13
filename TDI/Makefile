## Simple SDL mini code

CC=gcc

CPPFLAGS= `pkg-config --cflags sdl` `pkg-config --cflags gtk+-3.0`
CFLAGS= -Wall -Wextra -pedantic -std=c99 -O2
LDFLAGS= -rdynamic
LDLIBS= `pkg-config --libs sdl` -lSDL_image `pkg-config --libs gtk+-3.0`

SRC= main.c
OBJ= ${SRC:.c=.o}

all: main

main: ${OBJ}

clean:
	rm -f *~ *.o
	rm -f OCRoj
	rm -f main

# END
