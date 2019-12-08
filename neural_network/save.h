#ifndef SAVE_H
#define SAVE_H

#include <stdio.h>
#include <stdlib.h>
#include <err.h>
#include "nn.h"

//#define MAX_SIZE_LINE 10

void load_weight_bias(neural_net* net);
void save_weight_bias(neural_net* net);

#endif
