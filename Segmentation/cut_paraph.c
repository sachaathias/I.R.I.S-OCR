#include <stdio.h>
#include "cut_paraph.h"
#include "../DataStruct/data_struct.c"

// Return 1 if the line at the index is blank else return 0
int detect_blank_line(int image[][], size_t width, int index)
{
	for(int j = 0; j < width; j++)
	{
		if(image[index][j] == 1)
		{
			return 0;
		}
	}
	return 1;
}

//Return 1 if the column at the index is blank else return 0
int detect_blank_column(int image[][], size_t height, int index)
{
	for(int i = 0; i < height; i++)
	{
		if(image[i][index] == 1)
		{
			return 0;
		}
	}
	return 1;
}

// Delete blank side
void delete_black_side(int image[][], size_t height, size_t width)
{
	// Detect the corner at the top left
	int j1 = 0;
	while(detect_blank_column(image, height, j1))
	{
		j1++;
	}
	int i1 = 0;
	while(detect_blank_line(image, width, i1))
	{
		i1++;
	}

	// Detect the corner at the bottom right
	int j2 = width;
	while(detect_blank_column(image, height, j2))
	{
		j2--;
	}
	int i2 = height;
	while(detect_blank_line(image, width, i2))
	{
		i2--;
	}

	// Cut
	int new_image[height-i1-(height-i2)][width-j1-(width-j2)];
	for(int x = 
}




// Average line spacing




// Detect the begining and the end of each paragraph
void detect_paraph(int image[][], size_t height, size_t width, File *f)
{
	int i = 0;

	while( i < height)
	{
		int n = 0; // Number of consecutive blank line

		while(detect_blank_line(image, width, i))
		{
			n++;
			i++;
		}

		if(n >= 30) // Paragraph Spacing = 30px
		{
			enfiler(f,i); // Keep the begin index
		}

		while(!detect_blank_line(image, width, i))
		{
			i++
		}
		enfiler(f,i); // Keep the end index
	}
}

