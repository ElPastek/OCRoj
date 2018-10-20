## Simple SDL mini code

CC=gcc

CPPFLAGS= `pkg-config --cflags sdl` 
CFLAGS= -Wall -Wextra -std=c99 
LDFLAGS= -pthread -lpthread -rdynamic
LDLIBS= `pkg-config --libs sdl` -lSDL_image

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
