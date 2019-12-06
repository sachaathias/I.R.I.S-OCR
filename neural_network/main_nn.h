#ifndef MAIN_NN_H
#define MAIN_NN_H

#include "nn.h"
#include "save.h"
#include "train_tools.h"
#include <time.h>

#define RED "\033[0;31m"
#define GREEN "\033[0;32m"
#define DEFAULT "\033[0;0m"

void train();
neural_net *init_net_train();

#endif
