#ifndef CHARACTERE_H
#define CHARACTERE_H

// SYSTEM
#include <stdio.h>
#include <stdlib.h>
#include <err.h>
//#include "dataStruct.h"

// SDL
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "../../ImageOperations/binarise.h"
#include "../../ImageOperations/binarise.c"
#include "../../ImageTools/image_tools.h"
#include "../../ImageTools/image_tools.c"

// FUNCTIONS
int is_blank_column(SDL_Surface *image, int x, int y);
void add_column(SDL_Surface *image, int x, int y);
void split_band(SDL_Surface *image, int y);
void split_all_band(SDL_Surface *image, List indexs);

#endif

