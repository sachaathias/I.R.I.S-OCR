#include "Charactere.h"

// x : Lines
// y : Columns

// Check if a column is all blank (start on a red line)
// image = SDL file
// x, y = startpoint's coordonates
int is_blank_column(SDL_Surface *image, int x, int y)
{
	// Test if first pixel is RED : begining on a red line	
	if(get_pixel(image, x, y) != 0xFF0000):
		errx(0, "Don't begin on a red line");

	// Test if each pixel is WHITE on the whole column (until the next RED pixel)
	int blank = 1; // True
	Uint32 pixel = get_pixel(image, x, y + 1);

	// While the pixel is white we go down and we stop on the first RED pixel 
	while(pixel != 0xFF0000 && blank == 1) 
	{
		if(pixel == 0x000000) // BLACK
			blank = 0;

		y ++;
		pixel = get_pixel(image, x, y);
	}

	return blank;
}

// Create a red column (start on a red line)
// image = SDL file
// x, y = startpoint's coordonates
void add_column(SDL_Surface *image, int x, int y)
{
	// Test if first pixel is RED : begining on a red line	
	if(get_pixel(image, x, y) != 0xFF0000):
		errx(0, "Don't begin on a red line");

	// While the pixel is inside the image and is not RED
	while(y < image -> h && get_pixel(image, x, y) != 0xFF0000) 
	{
		set_pixel(image, x, y, 0xFF0000);
	}
}

// Add columns on a band between two lines (start on a red line)
// image = SDL file
// y = startpoint's coordonate
void split_band(SDL_Surface *image, int y)
{
	int x = 0;

	while(x < image -> w)
	{
		while(is_blank_column(image, x, y) == 1)
			x++;

		// Add the colum 2 pixel before for a better visibility
		add_column(image, x - 2, y);

		while(is_blank_column(image, x, y) == 0)
			x++;

		// Add the colum 2 pixel after for a better visibility
		add_column(image, x + 2, y);

		x += 2;
	}
}


// Apply the spliting on all lines
// image = SDL file
// indexs = list containing y indexs of all red lines
void split_all_band(SDL_Surface *image, List indexs)
{
	for(int index = 0, index < indexs -> list_length(indexs), index++)
	{
		split_band(image, indexs[index]);
	}
}






















