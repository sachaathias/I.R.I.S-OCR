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

	SDL_Surface* surface = load_image(file);
	SDL_Surface *screen = display_image(surface);
	//wait_for_keypressed();


	to_grey(surface);
	update_surface(screen, surface);
	wait_for_keypressed();

	to_black_and_white(surface);
	update_surface(screen, surface);
	wait_for_keypressed();

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
	square(surface, corner) ;
	update_surface(screen, surface);
	wait_for_keypressed();
	SDL_FreeSurface(screen);
	
	//CROP
	// corner[0] = x.left
	//corner[1] = x.right
	//corner[2] = y.top
	//corner[3] = y.bottom
	
		
	int Upper_X = corner[0]+1;
	int Upper_Y = corner[2]+1;
	int Width   = corner[1]-corner[0]-1;
	int Height  = corner[3]-corner[2]-1;

	crop_picture(surface,
		Upper_X,
		Upper_Y,
		Width,
		Height,"first_cut.bmp");
	update_surface(screen, surface);

	SDL_Surface* image = load_image("first_cut.bmp");
	SDL_Surface *scree = display_image(image);

	
	// Split lines
	split_eachline(image, tableau);
	// The Boucle count how many lines are inside tableau
	int lenght = 0;
	size_t range =10;
	for (size_t i = 0; i < len ; i++)
	{
		if (tableau[i] == 0 && i > range)
		{
			break;
		}
		else
			if (tableau[i] == 0 && tableau[i+1] == 0)
				break;
			else
				lenght ++;
	}

	update_surface(screen, image);
	SDL_SaveBMP(image,"eachlines.bmp");
	wait_for_keypressed();

	// Split Words and Characteres
	split_all_band(image, tableau, 0);
	update_surface(screen, image);
	SDL_SaveBMP(image,"eachCharacteres.bmp");

	// Save each line in files
	int number_picture = crop_Lines(image, tableau, lenght,0);
	wait_for_keypressed();

	SDL_Surface* Lines; 
	// Show each line previously saved
	char str[12];
	for( int count = 0; count < number_picture ;count++)
	{
		sprintf(str,"line%d.bmp",count);
		Lines = load_image(str);
		scree = display_image(Lines);
		update_surface(screen, image);
		wait_for_keypressed();
	}

	SDL_FreeSurface(surface);
	SDL_FreeSurface(scree);
	SDL_FreeSurface(image);
	SDL_FreeSurface(Lines);
	
	SDL_Quit();
}
