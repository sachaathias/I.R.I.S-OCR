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
	//reverseByte(bb);
	SDL_SaveBMP(bb,str);
	printf("%s\n",str);
}



void crop_Lines(SDL_Surface* image, int array[],int len)
{
	int Upper_line;
	int Bottom_line;
	int Height;
	int Width = image -> w;
	char str[]= "line.bmp";

	int i = 0;
	int count = 0 ;
	// Cross the array for getting each red lines's coordinates
	for (int index = 0; index < len; index++)
	{
		if (array[index] == 0 && index > 10 )
			break;
		Upper_line = array[index];
		index ++;
		Bottom_line =array[index];

		Height = Bottom_line - Upper_line;

		//sprintf(str,"line%d.bmp",i);
		printf("croped");
		crop_picture( image, 0,Upper_line+1, Width, Height-1,str);
		i++;
		count += crop_Letters(str, count);
	}
}

int check_pixel(SDL_Surface *image,int x)
{
	int y = 0;
	int Bool = 1;
	Uint32 pixel = get_pixel(image,x,y);

	if(pixel != 0x0000FF)
		Bool = 0;
	return Bool;
}


int crop_Letters(char* str_,int count)
{
	
	SDL_Surface* lines =load_image(str_);
	int width  = lines -> w;
	int height = lines -> h;

	int x = 0;

	int firstColumn;
	int secondColumn;
	char str[1000];

	int i = count;

	while( x < width )
	{

		while(x < width && !check_pixel(lines,x))
		{
			x ++;
		}
		firstColumn = x;
		x++;
		while (x < width && !check_pixel(lines,x))
		{
			x++;
		}

		secondColumn = x;
		x++;
		if (x < width )
		{
			sprintf(str,"letter%d.bmp",i);
			crop_picture(lines,
					firstColumn +1, // x
					1,           // y
					secondColumn - firstColumn-1, // width
					height-1,       // height
					str);
			i++;
		}
	}
	return i;
}



