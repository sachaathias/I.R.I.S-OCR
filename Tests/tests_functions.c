#include "tests_functions.h"

void save_BMP_test(char* file)
{
	SDL_Init(SDL_INIT_VIDEO);
	SDL_Surface *surface = load_image(file);
	SDL_Surface *copy = copy_image(surface);
	to_grey(copy);
	SDL_SaveBMP(copy, "Images/Grey.bmp");
	to_black_and_white(copy);
	SDL_SaveBMP(copy, "Images/Black_and_White.bmp");
	SDL_Quit();
}