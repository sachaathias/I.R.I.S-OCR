#include "tests_functions.h"

/*void save_BMP_test(char* file)
{
	init_sdl();

	SDL_Surface *surface = load_image(file);
	SDL_Surface *copy = copy_image(surface);
	SDL_FreeSurface(surface);
	to_grey(copy);
	SDL_SaveBMP(copy, "Images/Grey.bmp");
	to_black_and_white(copy);
	SDL_SaveBMP(copy, "Images/Black_and_White.bmp");
	SDL_FreeSurface(copy);

	SDL_Quit();
}*/

void display_image_test(char* file)
{
	List *list = NULL;
	list_create(list);

	init_sdl();

	SDL_Surface *surface = load_image(file);
	SDL_Surface *screen = display_image(surface);
	wait_for_keypressed();

	to_grey(surface);
	update_surface(screen, surface);
	wait_for_keypressed();

	to_black_and_white(surface);
	update_surface(screen, surface);
	wait_for_keypressed();
	
	split_eachline(surface);
	update_surface(screen, surface);
	wait_for_keypressed();

/*	split_all_band(surface);
	update_surface(screen, surface);
	wait_for_keypressed();
*/
	SDL_FreeSurface(surface);
	SDL_FreeSurface(screen);

	SDL_Quit();
}
