#include "crop.h"

// x = the x location of the rectangle's upper left corner
// y = the y location of the rectangle's upper left corner
// w = the width of the rectangle
// h = the height of the rectangle

// This function transform a picture to a square picture of dimension n
SDL_Surface* square_picture(SDL_Surface* image, int n)
{
    // test if we can fill the square picture of length n
    if(image->h >= n || image->w >= n)
    {
        printf("Error, n is too small\n");
        return image;
    }
    else
    {
        // Create the new picture of length n
        SDL_Surface *square = SDL_CreateRGBSurface(0, n, n,
                image->format->BitsPerPixel, 0, 0, 0, 0);

        // Fill the new picture with 0
        for(int i = 0; i < n; i++)
        {
            for(int j = 0; j < n; j++)
            {
                set_pixel(square, i, j, 0xFFFFFF);
            }
        }


        int square_center = n / 2;
        int h = image->h;
        int w = image->w;

        // Find the point where we can copy in square
        int x = square_center - w / 2;
        int y = square_center - h / 2;

        // Copy in square on the center
        for(int i = 0; i < h; i++)
        {
            for(int j = 0; j < w; j++)
            {
                set_pixel(square, x + j, y + i, get_pixel(image, j, i));
            }
        }

        return square;
    }
}


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

}

SDL_Surface* crop_pictureLetter(SDL_Surface* image, int x, int y, int width, int height)
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
    return bb;
}

void add_space(char str[])
{
    SDL_Surface *bb = SDL_CreateRGBSurface(0,
            24,24,
            32,1, 1,1, 1);
    SDL_SaveBMP(bb,str);
}

void crop_Lines(SDL_Surface* image, int array[],int len, int *count)
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

        crop_picture( image, 0,Upper_line+1, Width, Height-1,str);
        i++;
        crop_Letters(str,count );
    }
}

int check_pixel(SDL_Surface *image,int x)
{
    int y = 0;
    int Bool = 0;
    Uint32 pixel = get_pixel(image,x,y);
    //if the pixel is different of blue
    if(pixel == 0xFF0000 )
        Bool = 1;
    return Bool;
}

   int IsGreenPixel(SDL_Surface* image,int x,int y)
   {
            Uint32 pixel = get_pixel(image,x,y);
            if(pixel != 0x00ff00)
                    return 0;
            return 1;
   }

int IsWhitePicture(SDL_Surface *Picture) {

    int IsWhite = 1;

    for (int i = 0; i < Picture->h && IsWhite; i++) {
        for (int j = 0; j < Picture->w && IsWhite; j++) {

            Uint32 pixel = get_pixel(Picture,i,j);

            if (pixel == 0x000000)
                IsWhite = 0;
        }
    }

    return IsWhite;
}



void crop_Letters(char* str_,int *count)
{
    SDL_Surface* lines =load_image(str_);
    int width  = lines -> w;
    int height = lines -> h;

    int x = 0;

    int firstColumn;
    int secondColumn;
    char str[1000];


    while( x < width )
    {

        while(x < width && check_pixel(lines,x))
        {
            x ++;
        }

        if (IsGreenPixel(lines,x,0))
            {
                *count+=1;
                sprintf(str,"letter%d.bmp",*count);
                add_space(str);
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
            *count+=1;
            sprintf(str,"letter%d.bmp",*count);
            SDL_Surface *Letter = crop_pictureLetter(lines,
                    firstColumn +1 , // x
                    1,           // y
                    secondColumn - firstColumn-1, // width
                    height-1);       // heigh

            //if(!IsWhitePicture(Letter))
                SDL_SaveBMP(Letter,str);
        }
    }
}



