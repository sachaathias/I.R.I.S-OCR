#include "paragraph.h"

// Test if the whole column is blank
// image = SDL file
// x = startpoint's coordonate
int Is_blank_column(SDL_Surface *image, int x)
{
	int y = 0;

	int blank = 1; // True
	Uint32 pixel = get_pixel(image, x, y);

	// While the pixel isn't black we go down and we stop at the bottom of the image
	while(y < image -> h && blank == 1) 
	{
		if(pixel == 0x000000) // BLACK
			blank = 0;

		y ++;

		pixel = get_pixel(image, x, y);
	}

	return blank;
}

// Test if the whole line is blank
// image = SDL file
// x, y = startpoint's coordonates
int Is_blank_line(SDL_Surface *image, int x, int y)
{
	x++;

	int blank = 1; // True
	Uint32 pixel = get_pixel(image, x, y);

	// While the pixel isn't black we go down and we stop at the bottom of the image
	while(x < image -> w && pixel != 0xFF0000 && blank == 1) 
	{
		if(pixel == 0x000000) // BLACK
			blank = 0;

		x ++;

		pixel = get_pixel(image, x, y);
	}

	return blank;
}

// Create a blue column
// image = SDL file
// x = startpoint's coordonates
void Add_column(SDL_Surface *image, int x)
{
	for(int y = 0; y < image -> h;  y++)
	{
		set_pixel(image, x, y, 0xFF0000);
	}
}

// Create a blue lines
// image = SDL file
// y = startpoint's coordonate
void Add_line(SDL_Surface *image, int x, int y)
{
	x++;
	while(x < image -> w && get_pixel(image, x, y) != 0xFF0000)
	{
		set_pixel(image, x, y, 0xFF0000);
		x++;
	}
}

// Create a blue square around the block of texte
void square(SDL_Surface *image, int tableau[])
{
	int width = image -> w;
	int height = image -> h;

	int x_left;
	int x_right;
	int y_top;
	int y_bottom;

	// Left edge
	x_left = 0;
	while(x_left < width && Is_blank_column(image, x_left) == 1)
	{
		x_left++;
	}

	Add_column(image, x_left-2);

	// Right edge
	x_right = width - 1;
	while(x_right >= 0 && Is_blank_column(image, x_right) == 1)
	{
		x_right--;
	}

	Add_column(image, x_right+4);

	// Top edge
	y_top = 0;
	while(y_top < height && Is_blank_line(image, x_left, y_top))
	{
		y_top++;
	}

	Add_line(image, x_left-2, y_top-2);

	// Top edge
	y_bottom = height - 1;
	while(y_bottom >=0 && Is_blank_line(image, x_left, y_bottom))
	{
		y_bottom--;
	}

	Add_line(image, x_left-2, y_bottom+2);

	// Add the 4 corners's coordonates in the table
	tableau[0] = x_left-2;
	tableau[1] = x_right+4;
	tableau[2] = y_top-2;
	tableau[3] = y_bottom+2;
}













