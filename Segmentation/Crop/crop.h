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
#include "../Characteres/Charactere.h"

// FUNCTIONS

void crop_picture(SDL_Surface* image, int x, int y,
		int width, int height, char str[]);
int crop_Lines(SDL_Surface* image, int array[], int len);
int crop_Letters(SDL_Surface** lines);

#endif
