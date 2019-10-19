#ifndef PARAGRAPH_H
#define PARAGRAPH_H

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
int Is_blank_column(SDL_Surface *image, int x);
int Is_blank_line(SDL_Surface *image, int x, int y);
void Add_column(SDL_Surface *image, int x);
void Add_line(SDL_Surface *image, int x, int y);
void square(SDL_Surface *image, int tableau[]);

// OTHER FUNCTIONS

#include "../Lines/lines.h"

#endif
