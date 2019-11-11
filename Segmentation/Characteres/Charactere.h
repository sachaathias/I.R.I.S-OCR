#ifndef CHARACTERE_H
#define CHARACTERE_H

// SYSTEM
#include <stdio.h>
#include <stdlib.h>
#include <err.h>

// SDL

#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "../../ImageOperations/binarise.h"
#include "../../ImageTools/image_tools.h"
// FUNCTIONS
extern int is_blank_column(SDL_Surface *image, int x, int y);
extern void add_column(SDL_Surface *image, int x, int y, Uint32 color);
void split_band(SDL_Surface *image, int y);
void split_all_band(SDL_Surface *image, int *array);

#endif

