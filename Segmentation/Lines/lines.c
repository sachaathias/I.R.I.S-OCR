#include <err.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include "../../ImageOperations/binarise.h"
#include "../../ImageOperations/binarise.c"
#include "../../ImageTools/image_tools.h"
#include "../../ImageTools/image_tools.c"



//Unint32 pixel = get_pixel(image,x y)
// x : Ligne
// y : Columnes

// Check if a line is all blank
int is_blank_line(SDL_Surface *image, int x)
{

	int _width = image -> w;
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

//Trace a red line
void trace(SDL_Surface *image, int x)
{
	int _width = image -> w;
	Uint32 red = 0xFF0000;

	for (int index = 0; index < _width; index ++) 
	{
		//Change value pixel color of a pixel
		set_pixel(image, x, index, red);
	}
}


void split_eachline(SDL_Surface *image)
{
	int _height = image -> h;
	int lines = 0;

	while(lines < _height)
	{
		// Case : We are outside a line
		while(is_blank_line(image, lines) == 1)
		{
			lines++;
		}

		// Upper redline
		trace(image, lines - 5);

		// Case : we are inside a line
		while(is_blank_line(image, lines) == 0)
		{
			lines++;
		}

		// Lower redline 
		trace(image , lines + 5);

		// It's for begin from the line
		lines += 5;
	}
}

void init_sdl()
{
    // Init only the video part.
    // If it fails, die with an error message.
    if(SDL_Init(SDL_INIT_VIDEO) == -1)
        errx(1,"Could not initialize SDL: %s.\n", SDL_GetError());
}

int main()
{
	/*
	SDL_Surface* image_surface;
	SDL_Surface* screen_surface;

	init_sdl();

	image_surface = load_image("my_image.jpg");

	split_eachline(image_surface);

	screen_surface = display_image(image_surface );

	update_surface( screen_surface, image_surface);

	// Free the image surface.
	SDL_FreeSurface(image_surface);
	//Free the screen surface.
	SDL_FreeSurface(screen_surface);
	*/





	SDL_Init(SDL_INIT_VIDEO);
	SDL_Surface *surface = load_image("my_image.jpg");
	SDL_Surface *copy = copy_image(surface);
	to_grey(copy);
	display(copy, "Images/Grey.bmp");
	to_black_and_white(copy);
	split_eachline(copy);
	SDL_Quit();

}







