#include "crop.h"

// x = the x location of the rectangle's upper left corner
// y = the y location of the rectangle's upper left corner
// w = the width of the rectangle
// h = the height of the rectangle


void crop_picture(SDL_Surface* image, int x, int y, int width, int height)
{
	SDL_Rect b ={x, y, width, height};
	SDL_UnlockSurface(image);
	SDL_Surface *bb = SDL_CreateRGBSurface(SDL_HWSURFACE, b.w, b.h, 32, 0, 0, 0, 0);
	SDL_BlitSurface(image,&b,bb,NULL);
	SDL_LockSurface(image);
	SDL_SaveBMP(bb,"image.bmp");
}

