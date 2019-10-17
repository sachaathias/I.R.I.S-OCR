#ifndef  LINES_H
#define  LINES_H

#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include "../../ImageOperations/binarise.h"
#include "../../ImageTools/image_tools.h"
#include "../../sdl/sdl_functions.h"


int is_blank_line(SDL_Surface *image, int x);
void trace(SDL_Surface *image, int x);
void split_eachline(SDL_Surface *image);

#endif
