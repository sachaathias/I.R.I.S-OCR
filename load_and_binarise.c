#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>

//Initialize the sdl library for image treatment
void init_sdl()
{
	if(SDL_Init(SDL_INIT_VIDEO) == -1)
	{
		perror("SDL_Init");
		fprintf(stderr, "SDL_Init : %s\n", SDL_GetError());
		exit(EXIT_FAILURE);
	}
}

//return the pixel
Uint8* pixel_ref(SDL_Surface *surface, unsigned x, unsigned y)
{
	int sizePixel = surface->format->BytesPerPixel;
	return (Uint8 *)surface->pixels + y * surface->pitch + x * sizePixel;
}

//change datas of the pixel at position (x,y) on the surface with pixel
void set_pixel_color(SDL_Surface *surface, unsigned x, unsigned y, Uint32 pixel)
{	
	Uint8 *p = pixel_ref(surface, x, y);

	switch(surface->format->BytesPerPixel)
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

//return the datas of the pixel at position (x,y) on the surface
Uint32 get_pixel(SDL_Surface *surface, unsigned x, unsigned y)
{
	Uint8 *p = pixel_ref(surface, x, y);

	switch(surface->format->BytesPerPixel)
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

//Load image file and if load success, return it
SDL_Surface* load_image(char* file)
{
	SDL_Surface *imageSurface = NULL;
	imageSurface = SDL_LoadBMP(file);
	
	if(!imageSurface)
	{
		perror("SDL_LoadBMP");
		fprintf(stderr, "SDL_LoadBMP : %s\n", SDL_GetError());
		exit(EXIT_FAILURE);
	}
	return imageSurface;
}



//************************************//
//****************TMP*****************//
//************************************//
	
	/*
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
}*/

void save_BMP(char* file)
{
	SDL_Init(SDL_INIT_VIDEO);
	SDL_Surface *surface = load_image(file);
	SDL_SaveBMP(surface, "test.bmp");
	SDL_Quit();
}
