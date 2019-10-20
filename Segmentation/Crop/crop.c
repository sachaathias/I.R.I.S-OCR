#include "crop.h"

// x = the x location of the rectangle's upper left corner
// y = the y location of the rectangle's upper left corner
// w = the width of the rectangle
// h = the height of the rectangle


void crop_picture(SDL_Surface* image, int x, int y, int width, int height,char str[])
{
	// Create a virtual rectangle
	SDL_Rect b ={x, y, width, height};
	SDL_UnlockSurface(image);
	// Create a new picture
	SDL_Surface *bb = SDL_CreateRGBSurface(0, 
			width, 
			height, 
			image->format->BitsPerPixel, 0, 0, 0, 0);
	// Create a copy of our picture 
	SDL_UnlockSurface(bb);
	SDL_BlitSurface(image,&b,bb,NULL);
	SDL_LockSurface(bb);
	//reverseByte(bb);
	SDL_LockSurface(image);
	SDL_SaveBMP(bb,str);
	printf("%s\n",str);
}



int crop_Lines(SDL_Surface* image, int array[],int len)
{
	int Upper_line;
	int Bottom_line;
	int Height;
	int Width = image -> w;
	char str[12];

	int i = 0;
	// Cross the array for getting each red lines's coordinates
	for (int index = 0; index < len; index++)
	{
		if (array[index] == 0 && index > 10 )
			break;
		Upper_line = array[index];
		index ++;
		Bottom_line =array[index];

		Height = Bottom_line - Upper_line;

		sprintf(str,"line%d.bmp",i);
		i++;
		printf("croped");
		crop_picture( image, 0,Upper_line, Width, Height,str);
	}
	return i; 
}

int crop_Letters(SDL_Surface** liness)
{
	SDL_Surface* lines = *liness;
	int width  = lines -> w;
	int height = lines -> h;

	int x = 0;

	int firstColumn;
	int secondColumn;
	char str[100000000];

	int i = 0;

	while( x < width )
	{
		while( is_blank_column(lines, x, 0))
		{
			x ++;
		}
		
		firstColumn = x;
		x++;

		while (!is_blank_column(lines, x, 0))
		{
			x++;
		}
		secondColumn = x;

		sprintf(str,"letter%d.bmp",i);
		crop_picture(lines,
				firstColumn, // x
				0,           // y
				secondColumn - firstColumn, // width
				height,       // height
				str);
		i++;
	}
	return i;
}



