#include "Paragraphe.h"

// Test if the whole column is blank
// image = SDL file
// x = startpoint's coordonate
int is_blank_column(SDL_Surface *image, int x)
{
	int y = 0;

	int blank = 1; // True
	Uint32 pixel = get_pixel(image, x, y + 1);

	// While the pixel isn't black we go down and we stop at the bottom of the image
	while(pixel != 0x000000 && blank == 1) 
	{
		if(pixel == 0x000000) // BLACK
			blank = 0;

		y ++;
		pixel = get_pixel(image, x, y);
	}

	return blank;
}

// Create a blue column 
// image = SDL file
// x = startpoint's coordonate
void add_column(SDL_Surface *image, int x)
{
	for(int y = 0, y < image -> h, y++)
	{
		set_pixel(image, x, y, 0x000FFF);
	}
}

// Create a blue square around the block of texte
void square(SDL_Surface *image)
{
	int width = image -> w;
	int height = image -> h;


	int x;
	int y;

	// Left edge
	x = 0;
	while(is_blank_column(image, x) == 1)
	{
		x++;
	}

	add_column(image, x - 2);

	// Right edge
	x = width - 1;
	while(is_blank_column(image, x) == 1)
	{
		x--;
	}

	add_column(image, x + 2);

	// Top edge
	y = 0;
	while(is_blank_line(image, y))
	{
		y++;
	}

	trace(image, y);

	// Top edge
	y = height - 1;
	while(is_blank_line(image, y))
	{
		y--;
	}

	trace(image, y);
}













