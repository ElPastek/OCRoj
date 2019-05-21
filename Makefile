## Simple SDL mini code

CC=gcc
CFLAGS= -Wall  -Wextra -pedantic -std=c99
LDFLAGS= -rdynamic
LDLIBS= -lm `pkg-config --libs sdl` -lSDL_image `pkg-config --libs gtk+-3.0`

SRC= ocroj.c 
OBJ= ${SRC:.c=.o}

all: CFLAGS += -O2
all: ocroj

debug: CFLAGS += -g -O0
debug: ocroj

main: ${OBJ}

clean:
	rm -f *~ *.o
	rm -f ocroj

# END MDRRR
#-Werror
