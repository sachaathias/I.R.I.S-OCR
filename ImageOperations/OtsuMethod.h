#ifndef OTSUMETHOD_FUNCTIONS_H
#define OTSUMETHOD_FUNCTIONS_H

#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL.h>
#include "SDL/SDL_image.h"
#include "../ImageTools/image_tools.h"
#include <math.h>





/*
void get_histo(SDL_Surface *image,int histo[]);
void OmegaMyuGeneration(double prob[],double omega[],double myu[]);
void Sigma_Maximization(double *max_sigma,double sigma[],double myu[],
								Uint32 *threshold,double omega[]);
void Binarisation(SDL_Surface *image,Uint32 threshold);
*/
unsigned long *get_histogram(SDL_Surface* grey_image, unsigned long *histo);
Uint8 get_threshold(unsigned long *histo,int total);
void Otsu(SDL_Surface *image);

#endif
