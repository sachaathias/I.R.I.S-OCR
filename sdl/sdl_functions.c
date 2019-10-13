#include "sdl_functions.h"

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