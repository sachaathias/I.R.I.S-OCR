#include "OtsuMethod.h"


unsigned long *get_histogram(SDL_Surface* grey_image, unsigned long *histo)
{
				for(int i = 0; i < grey_image->h; i++)
								for(int j = 0; j < grey_image->w; j++)
								{
												Uint8 pixel = get_pixel(grey_image,j,i);
												if(histo[pixel] < 4294967295)
																histo[pixel] += 1;
								}
				return histo;
}

Uint8 get_threshold(unsigned long *histo, int total)
{
				unsigned long sum = 0, wf = 0, sumb = 0;
				unsigned long mb, mf;
				float between = 0, max = 0;
				Uint32 threshold1 = 0, threshold2 =0;
				for(int i = 0; i < 256; i++)
								sum += i * histo[i];
				unsigned long wb = 0;
				for(int i = 0; i < 256; i++)
				{
								wb += histo[i];
								if(wb == 0)
												continue;
								wf = total - wb;
								if( wf == 0)
												break;
								sumb += i * histo[i];
								mb = sumb / wb;
								mf = (sum - sumb) / wf;
								between = wb * wf * (mb - mf) * (mb - mf);
								if(between >= max)
								{
												threshold1 = i;
												if(between > max)
																threshold2 = i;
												max = between;
								}
				}
				Uint8 threshold = ((threshold1 + threshold2) / 2);
				return threshold;
}

void Binarize(SDL_Surface* image,Uint8 threshold)
{
				for(int i = 0; i < image->h; i++)
				{
								for(int j = 0; j < image->w; j++)
								{
												Uint8 pixel = get_pixel(image,j,i);
												if(pixel > threshold)
															set_pixel(image,j,i,0xFFFFFF);
												else
															set_pixel(image,j,i,0x000000);
								}
				}
}

void Otsu(SDL_Surface* image)
{
				unsigned long *histo = malloc(256*sizeof(unsigned long));
				for (int i = 0 ; i < 256; i ++)
								histo[i]=0;
				histo=get_histogram(image,histo);

				Uint8 threshold = get_threshold(histo,image->h*image->w);
				Binarize(image,threshold);
				free(histo);
}

