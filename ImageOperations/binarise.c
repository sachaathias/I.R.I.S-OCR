#include "binarise.h"

//Change the color to nuances of grey
void to_grey(SDL_Surface *surface)
{
	Uint32 pixel;
	Uint8 r, g, b;

	for(int i = 0; i < surface->w; i++)
	{
		for(int j = 0; j < surface->h; j++)
		{
			pixel = get_pixel(surface, i, j);
			SDL_GetRGB(pixel, surface->format, &r, &g, &b);
			Uint8 grey = 0.299 * r + 0.587 * g + 0.114 * b;
			pixel = SDL_MapRGB(surface->format, grey, grey, grey);
			set_pixel(surface, i, j, pixel);
		}
	}
}

//Change the color to black and white (it is a simple technique but it is one which get better results)
void to_black_and_white(SDL_Surface *surface)
{
	Uint32 pixel;
	Uint8 r, g, b;

	for(int i = 0; i < surface->w; i++)
	{
		for(int j = 0; j < surface->h; j++)
		{
			pixel = get_pixel(surface, i, j);
			SDL_GetRGB(pixel, surface->format, &r, &g, &b);

			if(r  <= 127)
				pixel = SDL_MapRGB(surface->format, 0, 0, 0);
			else
				pixel = SDL_MapRGB(surface->format, 255, 255, 255);
			set_pixel(surface, i, j, pixel);
		}
	}
}
