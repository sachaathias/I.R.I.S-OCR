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
	init_sdl();

	SDL_Surface *surface = load_image(file);
	SDL_Surface *screen = display_image(surface);
	//wait_for_keypressed();


	to_grey(surface);
	update_surface(screen, surface);
	//wait_for_keypressed();

	to_black_and_white(surface);
	update_surface(screen, surface);
	//wait_for_keypressed();

	//init values
	//
	int height = surface -> h;
	int width  = surface -> w;

	// Array that contain every red line's index
	// Array's pointeur
	size_t len = height*width;
	int *tableau = calloc(len, sizeof(int));

	int *corner = calloc(4, sizeof(int));

	// Make a square around the block text
	square(surface);
	update_surface(screen, surface);
	wait_for_keypressed();
	
	//CROP
	// corner[0] = x.left
	// corner[1] = x.right
	// corner[2] = y.top
	// corner[3] = y.bottom
	
	SDL_Surface *crop_surface = crop_picture(surface,corner[0], corner[2], corner[1]- corner[0], corner[3] - corner[2]);
	screen = display_image(crop_surface);



	/*
	// Split lines
	split_eachline(surface, tableau);
	update_surface(screen, surface);
	wait_for_keypressed();

	// Split Words and Characteres
	split_all_band(surface, tableau);
	update_surface(screen, surface);
	*/
	wait_for_keypressed();

	SDL_FreeSurface(surface);
	SDL_FreeSurface(screen);

	SDL_Quit();
}
