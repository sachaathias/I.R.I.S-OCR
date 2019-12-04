#include "tests_functions.h"

void display_image_test(char* file)
{
	init_sdl();

	SDL_Surface* surface = load_image(file);
	SDL_Surface *screen = display_image(surface);
	//wait_for_keypressed();


	to_grey(surface);
	update_surface(screen, surface);
	wait_for_keypressed();

	//to_black_and_white(surface);
	Otsu(surface);
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
	split_all_band(image, tableau);
	update_surface(screen, image);
	SDL_SaveBMP(image,"eachCharacteres.bmp");

	int count = 0;//the variable count how many letter there are inside 
	// the picture
	int *p = &count;
	// ---Save each letter -----
	crop_Lines(image, tableau, lenght, p);
	wait_for_keypressed();



	// ------ Picture To Matrix --------
	int nbr_of_letter = *p;

	int c = 1;
	SDL_Surface* letter;
	char Name[1000];
	while(c < nbr_of_letter)
	{
		sprintf(Name,"letter%d.bmp",c);
		letter = load_image(Name);
		SDL_Surface* new = square_picture(letter, 60);
		//screen = display_image(new);
		//wait_for_keypressed();
		struct matrix *data = newMatrix(new->h,new->w);
		for(int i = 0; i < new->h; i++)
		{
			for(int j = 0; j < new->w; j++)
			{
				Uint32 pixel = get_pixel(new,j,i);
			
				if(pixel == 0x000000)
					setElement(data , i, j, (double) 1);
				else
					setElement(data , i, j, (double) 0);
			}
		}
		//printMatrix(data);
    //struct matrix *ResizePlus = scale_up(data,80,80);
    //printMatrix(ResizePlus);
    struct matrix *ResizeMoins = scale_down(data,40,40);
    printMatrix(ResizeMoins);
		// ENVOI AU RESEAU DE NEURONE
		printf("letter %d/%d \n",c,nbr_of_letter);
		c++;
		free(data);
	}
	// free all pointer
	//free(corner);
	//free(tableau);
	//free(p);
	//SDL_FreeSurface(letter);
	//SDL_FreeSurface(surface);
	//SDL_FreeSurface(image);
	//SDL_Quit();
}
