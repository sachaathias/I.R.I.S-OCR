#ifndef CROP_H
#define CROP_H

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

void crop_picture(SDL_Surface* image, int x, int y,
		int width, int height);

#endif
