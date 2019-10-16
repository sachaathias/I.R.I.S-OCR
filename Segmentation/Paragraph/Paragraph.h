#ifndef PARAGRAPHE_H
#define PARAGRAPHE_H

// SYSTEM
#include <stdio.h>
#include <stdlib.h>
#include <err.h>

// SDL
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "../../ImageOperations/binarise.h"
#include "../../ImageOperations/binarise.c"
#include "../../ImageTools/image_tools.h"
#include "../../ImageTools/image_tools.c"

// FUNCTIONS
int is_blank_column(SDL_Surface *image, int x);
void add_column(SDL_Surface *image, int x);
void square(SDL_Surface *image);

// OTHER FUNCTIONS
#include "dataStruct.h"
#include "../Lines/lines.h"

#endif