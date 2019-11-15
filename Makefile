
CC = gcc

CFLAGS = -Wall -Wextra -Werror -std=c99 -g #-fsanitize=address
LDFLAGS = #-fsanitize=address
LDLIBS = -lSDL -lSDL_image -lm

SRC = main.c \
      ImageOperations/binarise.c \
	  ImageTools/image_tools.c \
	  sdl/sdl_functions.c\
	  Tests/tests_functions.c\
	  Segmentation/Lines/lines.c\
	  Segmentation/Characteres/Charactere.c\
	  Segmentation/Paragraph/paragraph.c\
	  Segmentation/Crop/crop.c\
	  XOR/nn_xor.c\
	  Segmentation/ToMatrix/to_matrix.c\
	  matrix.c

OBJ = $(SRC:.c=.o)
DEP = $(SRC:.c=.d)

all: main

-include $(DEP)

main: $(OBJ)

clean:
	rm -f $(OBJ) $(DEP) main
	rm -f *.bmp

