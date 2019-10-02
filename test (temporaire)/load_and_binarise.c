#include <stdio.h>
#include <SDL2/SDL.h>

void set_pixel_color(SDL_Surface *surface, int x, int y, Uint32 pixel)
{
	int sizePixel = surface->format->BytesPerPixel;
	
	Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * sizePixel;

	switch(sizePixel)
	{
		case 1:
			*p = pixel;
			break;
		case 2:
			*(Uint16 *)p = pixel;
			break;
		case 3:
			if(SDL_BYTEORDER == SDL_BIG_ENDIAN)
			{
				p[0] = (pixel >> 16) & 0xff;
				p[1] = (pixel >> 8) & 0xff;
				p[2] = pixel & 0xff;
			}
			else
			{
				p[0] = pixel & 0xff;
				p[1] = (pixel >> 8) & 0xff;
				p[2] = (pixel >> 16) & 0xff;
			}
			break;
		case 4:
			*(Uint32 *)p = pixel;
			break;
	}	
}

Uint32 get_pixel_color(SDL_Surface *surface, int x, int y)
{
	int sizePixel = surface->format->BytesPerPixel;

	Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * sizePixel;

	switch(sizePixel)
	{
		case 1:
			return *p;
		case 2:
			return *(Uint16 *)p;
		case 3:
			if(SDL_BYTEORDER == SDL_BIG_ENDIAN)
				return p[0] << 16 | p[1] << 8 | p[2];
			else
				return p[0] | p[1] << 8 | p[2] << 16;
		case 4:
			return *(Uint32 *)p;
		default:
			return 0;
	}
}

SDL_Surface *load_image(char* file)
{
//	SDL_Init(SDL_INIT_VIDEO);
	SDL_Surface *imageSurface = SDL_LoadBMP(file);

	int width = imageSurface->w;
	int height = imageSurface->h;

	for(int i = 0; i < width; i++)
	{
		for(int j = 0; j < height; j++)
		{
			Uint32 pixel = get_pixel_color(imageSurface, i, j);
			Uint8 r, g, b, a;
			SDL_GetRGBA(pixel, imageSurface->format, &r, &g, &b, &a);
			
			Uint32 med = (r + g + b) / 3;

			if(med > 128)
				pixel = SDL_MapRGBA(imageSurface->format, 255, 255, 255, 1);
			else
				pixel = SDL_MapRGBA(imageSurface->format, 0, 0, 0, 1);

			set_pixel_color(imageSurface, i, j, pixel);		
		}
	}

	return imageSurface;
}

void save_BMP(char* file)
{
	SDL_Init(SDL_INIT_VIDEO);
	SDL_Surface *surface = load_image(file);
	SDL_SaveBMP(surface, file);
	SDL_Quit();
}
