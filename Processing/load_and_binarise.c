#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

//Initialize the sdl library for image treatment
void init_sdl()
{
	if(SDL_Init(SDL_INIT_VIDEO) == -1)
	{
		perror("SDL_Init");
		fprintf(stderr, "SDL_Init: %s\n", SDL_GetError());
		exit(EXIT_FAILURE);
	}
}

//return the pixel
Uint8* pixel_ref(SDL_Surface *surface, int x, int y)
{
	int sizePixel = surface->format->BytesPerPixel;
	return (Uint8 *)surface->pixels + y * surface->pitch + x * sizePixel;
}

//change datas of the pixel at position (x,y) on the surface with pixel
void set_pixel(SDL_Surface *surface, int x, int y, Uint32 pixel)
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
Uint32 get_pixel(SDL_Surface *surface, int x, int y)
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
	imageSurface = IMG_Load(file);
	
	if(!imageSurface)
	{
		perror("IMG_Load");
		fprintf(stderr, "IMG_Load: %s\n", SDL_GetError());
		exit(EXIT_FAILURE);
	}
	return imageSurface;
}

//Copy image and change the color to black and white
SDL_Surface* copy_image_bw(SDL_Surface *surface)
{
	Uint32 pixel;
	Uint8 r, g, b;
	SDL_Surface *copy = NULL;
	copy = SDL_CreateRGBSurface(0, surface->w, surface->h, surface->format->BitsPerPixel, 0, 0, 0, 0);

	if(copy == NULL)
	{
		perror("SDL_CreateRGBSurface");
		fprintf(stderr, "SDL_CreateRGBSurface: %s\n", SDL_GetError());
		exit(EXIT_FAILURE);
	}

	for(int i = 0; i < surface->w; i++)
	{
		for(int j = 0; j < surface->h; j++)
		{
			pixel = get_pixel(surface, i, j);
			SDL_GetRGB(pixel, surface->format, &r, &g, &b);
			Uint32 med = (r + g + b) / 3;
			
			if(med > 128)
				pixel = SDL_MapRGB(surface->format, 255, 255, 255);
			else
				pixel = SDL_MapRGB(surface->format, 0, 0, 0);
			set_pixel(copy, i, j, pixel);
		}
	}

	return copy;
}


//************************************//
//****************TMP*****************//
//************************************//

void save_BMP(char* file)
{
	SDL_Init(SDL_INIT_VIDEO);
	SDL_Surface *surface = load_image(file);
	SDL_Surface *copy = copy_image_bw(surface);
	SDL_SaveBMP(copy, "test.bmp");
	SDL_Quit();
}
