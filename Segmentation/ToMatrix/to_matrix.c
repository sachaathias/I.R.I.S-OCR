#include "to_matrix.h"

void to_matrix(SDL_Surface* letter, int array[])
{
	int width = letter -> w;
	int height = letter -> h;

	for(int i = 0; i < height; i++)
	{
		for(int j = 0; j < width; j++)
		{
			Uint32 pixel = get_pixel(letter, i, j);
			
			if(pixel == 0xFFFFFF)
				array[i*width+j] = 0;
			else
				array[i*width+j] = 1;
		}
	}
}

void print_matrix(int array[], int width, int height)
{

	for(int i = 0; i < height; i++)
	{
		for(int j = 0; j < width; j++)
		{
			printf("%d  ",array[i*width+j]);
		}
		printf("\n");
	}
}



