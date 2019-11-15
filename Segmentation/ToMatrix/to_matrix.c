#include "to_matrix.h"
#include <stdio.h>

void to_matrix(SDL_Surface* letter, int array[])
{
	int width = letter -> w;
	int height = letter -> h;

	for(int i = 0; i < height; i++)
	{
		for(int j = 0; j < width; j++)
		{
			Uint32 pixel = get_pixel(letter, i, j);
			
			if(pixel == 0x000000)
				array[i*width+j] = 1;
			else
				array[i*width+j] = 0;
		}
	}
}

void print_matrix(int array[], int width, int height)
{

	for(int i = 0; i < height; i++)
	{
		for(int j = 0; j < width; j++)
		{
			if(array[i*width+j] == 1)
			{
				printf("\033[1;31m");	// Print in red
				printf("%4g",(double)array[i*width+j]);
				printf("\033[0m;");		// Reset color
			}
			else
				printf("%4g",(double)array[i*width+j]);
		}
		printf("\n");
	}

	printf("%d  %d", height, width);
}



