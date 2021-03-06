#ifndef TESTS_FUNCTIONS_H
#define TESTS_FUNCTIONS_H

#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL.h>
#include "SDL/SDL_image.h"
#include <SDL/SDL_rotozoom.h>
#include <unistd.h>
#include "../ImageOperations/binarise.h"
#include "../ImageOperations/OtsuMethod.h"
#include "../ImageTools/image_tools.h"
#include "../sdl/sdl_functions.h"
#include "../Segmentation/Lines/lines.h"
#include "../Segmentation/Characteres/Charactere.h"
#include "../Segmentation/Paragraph/paragraph.h"
#include "../Segmentation/Crop/crop.h"
#include "../matrix.h"
#include "../neural_network/main_nn.h"
#include "../neural_network/nn.h"


char* Segmentation_GUI(char* file);
void  Segmentation(char* file);

#endif
