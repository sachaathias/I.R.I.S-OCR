CC = gcc
CFLAGS = `pkg-config --cflags gtk+-3.0`  -O3
LDLIBS = `pkg-config --libs gtk+-3.0` -lSDL -lSDL_image
LDFLAGS= $(PTRHREAD) $(GTKLIB) -export-dynamic

SRC=interface.c
OBJ= ${SRC: .c=.o}
DEP= ${SRC:.c=d}

all: interface

interface: ${OBJ}

clean:
	${RM} $(EXE)
