#include <stdio.h>
#include <SDL2/SDL.h>

int init_SDL()
{
	if(0 != SDL_Init(SDL_INIT_VIDEO))
	{
		return 1;
	}
	SDL_Quit();
	return 0;  
}

SDL_Surface load_image(char file)
{
	if(init_SDL() == 1)
		return EXIT_FAILURE;
	SDL_Surface* imageSurface = SDL_LoadBMP(file);
	SDL_UnlockSurface(imageSurface);
	int* width = imageSurface.w;
	int* height = imageSurface.h;
	//BINARIZATION
}
