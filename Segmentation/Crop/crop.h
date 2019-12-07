#ifndef CROP_H
#define CROP_H

// SYSTEM
#include <stdio.h>
#include <stdlib.h>
#include <err.h>

// SDL
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include <SDL/SDL_rotozoom.h>
#include "../../ImageOperations/binarise.h"
#include "../../ImageTools/image_tools.h"
#include "../Characteres/Charactere.h"

// FUNCTIONS

SDL_Surface* square_picture(SDL_Surface* image, int n);
void crop_picture(SDL_Surface* image, int x, int y,
        int width, int height, char str[]);
SDL_Surface* crop_pictureLetter(SDL_Surface* image, int x, int y,
        int width, int height);
void crop_Lines(SDL_Surface* image, int array[], int len,int *count);
int check_pixel(SDL_Surface *image, int x);
void crop_Letters(char* str_,int *count);
void add_space(char str[]);
//int IsGreenPixel(SDL_Surface* image,int x,int y);

#endif
