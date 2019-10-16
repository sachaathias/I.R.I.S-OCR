#include <stdio.h>
#include <stdlib.h>
#include <err.h>

// Uint32 pixel = get_pixel(image, x, y)
// x : Lignes
// y : Columnes

// Check if a column is all blank
int is_blank_column(SDL_Surface *image, int index_x, int index_y)
{
	int y = index_y;

	// Test if first pixel is RED : begining on a red line
	Uint32 pixel = get_pixel(image, index, y);
	if(pixel != 0xFF0000):
		errx(0, "Don't begin on a red line");

	// Test if each pixel is WHITE on the whole column (until the next RED pixel)
	int blank = 1; // True
	pixel = get_pixel(image, index, y+1);

	// While the pixel is white we go down and we stop on the first RED  pixel 
	while(pixel != 0xFF0000 && blank == 1) 
	{
		if(pixel == 0x000000) // BLACK
			blank = 0;

		y ++;
		pixel = get_pixel(image, index, y);
	}

	return blank;
}

// Create a red column on a band between y1 and y2 (2 red lines)
//   y1 ->   -------------
//			  A  B  C  D  E
//   y2 ->   ------------- 
void add_column(SDL_Surface *image, int index_x, int index_y1, int index_y2)
{
	for(int y = index_y1; y < index_y2; y++)
	{
		Uint32 pixel = get_pixel(image, index_x, y);
		pixel = 0xFF0000
	}
}

// Add columns on a band between y1 and y2 (2 red lines)
//   y1 ->   -------------
//			  A  B  C  D  E
//   y2 ->   -------------  
void split_line_in_column(SDL_Surface *image, int index_y1, int index_y2)
{
	int width = image -> width;
	int x = 0;
	int y = index_y1;

	while(x < width)
	{
		while(is_blank_column(image, x, y) == 1)
			x++;

		// Add the colum 5 pixel before for a better visibility
		add_column(image, x - 5, y1, y2);

		while(is_blank_column(image, x, y) == 0)
			x++;

		// Add the colum 5 pixel after for a better visibility
		add_column(image, x + 5, y1, y2);

		x += 5;
	}
}


// Apply the spliting on all lines
void split_all_column(SDL_Surface *image)
{
	int height = image -> height;
	x = 0;

	// Follow the left edge of the image
	for(int y = 0, y < height; y++)
	{
		// If we meet a RED pixel (y1), run split_line_in_column
		Uint32 pixel = get_pixel(image, x, y);
		if(pixel == 0xFF0000)
	}

}






















