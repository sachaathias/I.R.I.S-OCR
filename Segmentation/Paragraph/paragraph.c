#include <err.h>
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "paragraph.h"
#include "ImageTools/image_tools.h"

//Unint32 pixel = get_pixel(image,x y)
// x : Ligne
// y : Columnes

int is_blank_line(SDL_Surface *image, int x)
{

	int _width = image -> width;
	int index = 0;
	// The boolean that the function return
	int Bool = 1;
	// The first pixel of the image
	Uint32 pixel = get_pixel(image,x,index);

	// We cross the line
	while (( index < _width) && (pixel == 0xFFFFFF))
	{
		pixel = get_pixel(image, x, index);
		index ++;
	}

	// Check if pixel isn't white 
	// Bool set as false if pixel isn't
	if( pixel!= 0xFFFFFF)
		Bool = 0;

	return Bool;
}

void split_paragph(SDL_Surface *image)

