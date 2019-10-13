#ifndef IMAGE_TOOLS_H
#define IMAGE_TOOLS_H

#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

void set_pixel(SDL_Surface *surface, int x, int y, Uint32 pixel);
Uint32 get_pixel(SDL_Surface *surface, int x, int y);
SDL_Surface* load_image(char* file);
SDL_Surface* copy_image(SDL_Surface *surface);
void save_BMP(SDL_Surface *surface, char* file);

#endif