#ifndef BINARISE_H
#define BINARISE_H

#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include "../ImageTools/image_tools.h"
#include "../sdl/sdl_functions.h"

#define MIN2(a,b) (((a)<(b))?(a):(b))
#define MAX2(a,b) (((a)>(b))?(a):(b))

extern void to_grey(SDL_Surface *surface);
extern void to_black_and_white(SDL_Surface *surface);

#endif
