#include "crop.h"

SDL_Surface* crop_picture(SDL_Surface* image, int x, int y,
		int width,int height)

{

    SDL_Surface* surface = SDL_CreateRGBSurface(image->flags, width, height,
			image->format->BitsPerPixel,
			image ->format->Rmask,
			image->format->Gmask,
			image->format->Bmask,
			image->format->Amask);

    SDL_Rect rect = 
	{
		x, y, width, height
	};

    SDL_BlitSurface(image, &rect, surface, 0);

    return surface;

}

