
CC = gcc -g


CFLAGS = `pkg-config --cflags gtk+-3.0` -Wall -Wextra -std=c99 -g -I/usr/include/SDL
LDLIBS =`pkg-config --libs gtk+-3.0`  -lSDL -lSDL_image -lm -lSDL_gfx
LDFLAGS = $(PTRHREAD) $(GTKLIB) -export-dynamic

SRC = main.c \
      ImageOperations/binarise.c \
	  ImageTools/image_tools.c \
	  sdl/sdl_functions.c\
	  Tests/tests_functions.c\
	  Segmentation/Lines/lines.c\
	  Segmentation/Characteres/Charactere.c\
	  Segmentation/Paragraph/paragraph.c\
	  Segmentation/Crop/crop.c\
	  matrix.c\
	  XOR/xor.c\
	  ImageOperations/OtsuMethod.c\
	  neural_network/nn.c\
	  neural_network/save.c\
	  neural_network/tools.c\
	  neural_network/train_tools.c\
	  neural_network/main_nn.c\
	  interface.c\

OBJ = $(SRC:.c=.o)
DEP = $(SRC:.c=.d)

all: main

-include $(DEP)

main: $(OBJ)

clean:
	rm -f $(OBJ) $(DEP) main
	rm -f *.bmp letter*.txt

