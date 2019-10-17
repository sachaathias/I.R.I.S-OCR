#include "lines.h"



//Unint32 pixel = get_pixel(image,x y)
// x : Ligne
// y : Columnes

// Check if a line is all blank
int is_blank_line(SDL_Surface *image, int y)
{

	int _width = image -> w;
	int x = 0;
	// The boolean that the function return
	int Bool = 1;
	// The first pixel of the image
	Uint32 pixel = get_pixel(image, x, y);

	// We cross the line
	while (( x < _width) && Bool)
	{
		pixel = get_pixel(image, x, y);
		if( pixel!= 0xFFFFFF)
			Bool = 0;
		x++;
	}

	return Bool;
}

//Trace a red line
void trace(SDL_Surface *image, int y)
{
	int _width = image -> w;
	Uint32 red = 0x0000FF;

	for (int index = 0; index < _width; index ++) 
	{
		//Change value pixel color of a pixel
		set_pixel(image,index,y, red);
	}
}


void split_eachline(SDL_Surface *image)
{
	int _height = image -> h;
	int lines = 0;

	while(lines < _height - 2)
	{
		// Case : We are outside a line
		while((lines < _height-2) &&
				(is_blank_line(image, lines) == 1))
		{
			lines++;
		}

		// Upper redline
		trace(image, lines-1);
		
		
		// Case : we are inside a line
		while(lines < _height-2 && 
			is_blank_line(image, lines) == 0)
		{
			lines++;
		}

		// Lower redline 
		trace(image , lines +1);
		lines ++;
		// It's for begin from the line
	}
}









