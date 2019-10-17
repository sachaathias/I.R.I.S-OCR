#Makefile

CC = gcc

CFLAGS = -Wall -Wextra -std=c99 -g
LDFLAGS =
LDLIBS = -lSDL -lSDL_image

SRC = main.c \
      ImageOperations/binarise.c \
	  ImageTools/image_tools.c \
	  sdl/sdl_functions.c\
	  Tests/tests_functions.c\
	  Segmentation/Lines/lines.c\
	  Segmentation/Characteres.c\
	  Segmentation/dataStruct.c
	  
OBJ = $(SRC:.c=.o)
DEP = $(SRC:.c=.d)

all: main

-include $(DEP)

main: $(OBJ)

clean:
	rm -f $(OBJ) $(DEP) main

#END
