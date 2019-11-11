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



int crop_Lines(SDL_Surface* image, int array[],int len)
{
	int Upper_line;
	int Bottom_line;
	int Height;
	int Width = image -> w;
	char str[]= "line.bmp";

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

		//sprintf(str,"line%d.bmp",i);
		printf("croped");
		crop_picture( image, 1,Upper_line, Width, Height,str);
		i++;
		crop_Letters(str);
	}
	return i; 
}
int check_column(SDL_Surface *image, int x, Uint32 color )
{
	int y = 0;
	int Bool = 1;
	Uint32 pixel = get_pixel(image,x,y);

	while(y < image -> h && Bool == 1 )
	{
		if (pixel != color )
			Bool = 0;
		y++;
	}
	return Bool;
}

int IsLetter(SDL_Surface *image, int x)
{
	int y = 0;
	int Bool = 0;
	Uint32 pixel = get_pixel(image,x,y);

	while(y < image -> h && Bool == 1 )
	{
		if (pixel == 0x000000 )
			Bool = 1;
		y++;
	}
	return Bool;
}

int crop_Letters(char* str_)
{
	printf("Hello");
	SDL_Surface* lines =load_image(str_);
	int width  = lines -> w;
	int height = lines -> h;

	int x = 0;

	int firstColumn;
	int secondColumn;
	char str[1000];

	int i = 0;

	while( x < width )
	{
		while(check_column(lines,x,0xFFFFFF) )
		{
			x ++;
		}

		if (check_column(lines,x ,0x00FF00))
		{
			x++;
		}

		if (check_column(lines,x,0x0000FF))
		{
			firstColumn = x;
			x++;
		}
		while (IsLetter(lines, x))
		{
			x++;
		}
		
		if(check_column(lines,x,0x0000FF))
		{
			secondColumn = x;
		}

		sprintf(str,"letter%d.bmp",i);
		crop_picture(lines,
				firstColumn, // x
				0,           // y
				secondColumn - firstColumn, // width
				height-1,       // height
				str);
		i++;
	}


	return i;
}



