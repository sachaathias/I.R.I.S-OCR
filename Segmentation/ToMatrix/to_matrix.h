#ifndef TO_MATRIX_H
#define TO_MATRIX_H

#include <stdio.h>
#include <stdlib.h>
#include <err.h>

#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "../../ImageOperations/binarise.h"
#include "../../ImageTools/image_tools.h"

void to_matrix(SDL_Surface* letter, int array[]);
void print_matrix(int array[], int width, int height);

#endif




