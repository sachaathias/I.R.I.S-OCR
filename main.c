#include <SDL2/SDL.h>
#include <stdio.h>

int main()
{
	if(0 != SDL_Init(SDL_INIT_VIDEO))
	{
		printf("FAIL");
        	return EXIT_FAILURE;
	}
	printf("SUCCESS");
	SDL_Quit();
	return EXIT_SUCCESS;
}
