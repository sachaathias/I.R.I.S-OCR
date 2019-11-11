#include "Charactere.h"
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "../../ImageOperations/binarise.h"
#include "../../ImageTools/image_tools.h"

// x : Lines
// y : Columns

// Check if a column is all blank (start on a red line)
// image = SDL file
// x, y = startpoint's coordonates
int is_blank_column(SDL_Surface *image, int x, int y)
{
	// Test if first pixel is RED : begining on a red line
	if(get_pixel(image, x, y) != 0x0000FF)
		errx(0, "Is blank ne demarre pas sur un pixel rouge");

	// Test if each pixel is WHITE on the whole column (until the next RED pixel)
	int blank = 1; // True
	Uint32 pixel = get_pixel(image, x, y + 1);

	// While the pixel is white we go down and we stop on the first RED pixel 
	while(y < image -> h && pixel != 0x0000FF && blank == 1) 
	{
		if(pixel == 0x000000) // BLACK
			blank = 0;

		y++;

		pixel = get_pixel(image, x, y);
	}

	return blank;
}

// Create a red column (start on a red line)
// image = SDL file
// x, y = startpoint's coordonates
// color = color of the pixel
void add_column(SDL_Surface *image, int x, int y, Uint32 color)
{
	//printf("%d  %d\n",x, y);
	// Test if first pixel is RED : begining on a red line	
	if(get_pixel(image, x, y) != 0x0000FF)
		errx(0, "add colonn pas sur un pixel rouge");

	y++;

	// While the pixel is inside the image and is not RED
	while(y < image -> h-1 && get_pixel(image, x, y) != 0x0000FF) 
	{
		set_pixel(image, x, y, color);
		y++;
	}
}

// Add columns on a band between two lines (start on a red line)
// image = SDL file
// y = startpoint's coordonate
void split_band(SDL_Surface *image, int y)
{
	int width = image -> w;
	int x = 0;


	while(x < width - 30)
	{
		// If this variable goes beyond 5 pixel, this is a word space
		// Else this is a char space
		int space = 0;

		while(x < width-1 && is_blank_column(image, x, y) == 1)
		{
			x++;
			space++;
		}

		x++;

		if(space > 5)
		{
			if(space < 20)
			{
				// Space word : Green Column
				add_column(image, x-2, y, 0x00FF00);
				add_column(image, x-1, y, 0x0000FF);
			}
		}
		else
			// Space char : Red Column
			add_column(image, x-1, y, 0x0000FF);

		if(space < 20)
		{
			while(x < width-1 && is_blank_column(image, x, y) == 0)
				x++;

			// Add the colum 2 pixel after for a better visibility
			add_column(image, x, y, 0x0000FF);

			x ++;
		}
	}
}


// Apply the spliting on all lines
// image = SDL file
// array = list containing y indexs of all red lines
void split_all_band(SDL_Surface *image, int *array)
{
	for(int index = 0; index < image -> h-6; index+=2)
	{
		if(array[index] ==0 && index > 10 )
			break;
		else
			split_band(image, array[index]);
	}
}






















