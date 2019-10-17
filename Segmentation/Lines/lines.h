#ifndef "LINES_H"
#define "LINES_H"

#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include "../../ImageOperations/binarise.h"
#include "../../ImageOperations/binarise.c"
#include "../../ImageTools/image_tools.h"
#include "../../ImageTools/iamge_tools.c"


int is_blank_line(SDL_Surface *image, int x);
void trace(SDL_Surface *image, int x);
void split_eachline(SDL_Surface *image);
void init_sdl();

#endif
