#Makefile

CC = gcc

CFLAGS = -Wall -Wextra -std=c99 -g
LDFLAGS =
LDLIBS = -lSDL2

SRC = main.c \
      load_and_binarise.c
OBJ = $(SRC:.c=.o)
DEP = $(SRC:.c=.d)

all: main

-include $(DEP)

main: $(OBJ)

clean:
	rm -f $(OBJ) $(DEP) main

#END
