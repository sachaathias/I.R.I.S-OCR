#include "crop.h"

// x = the x location of the rectangle's upper left corner
// y = the y location of the rectangle's upper left corner
// w = the width of the rectangle
// h = the height of the rectangle


void crop_picture(SDL_Surface* image, int x, int y, int width, int height,char str[])
{
	SDL_Rect b ={x, y, width, height};
	SDL_UnlockSurface(image);
	SDL_Surface *bb = SDL_CreateRGBSurface(0, 
			width, 
			height, 
			image->format->BitsPerPixel, 0, 0, 0, 0);
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
