#ifndef NN_H
#define NN_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <err.h>
#include "../matrix.h"
#include "tools.h"

#define NB_INPUT 28*28
#define NB_HIDDEN 20
#define NB_OUTPUT 52

typedef struct
{
    size_t nb_input;
    size_t nb_hidden;
    size_t nb_output;

    double input[NB_INPUT];
    double hidden[NB_HIDDEN];
    double output[NB_OUTPUT];

    double w_IH[NB_INPUT * NB_HIDDEN];
    double w_HO[NB_HIDDEN * NB_OUTPUT];

    double b_H[NB_HIDDEN];
    double b_O[NB_OUTPUT];

    double delta_w_IH[NB_INPUT * NB_HIDDEN];
    double delta_w_HO[NB_HIDDEN * NB_OUTPUT];

    double delta_b_H[NB_HIDDEN];
    double delta_b_O[NB_OUTPUT];

    double goal[NB_OUTPUT];

    double cost;
    double learning_rate;
    double alpha;
} neural_net;

neural_net* init_net();
char forward(neural_net* net, double* input, char expected);
void backward(neural_net* net);
void update_weights(neural_net* net);
void update_biases(neural_net* net);
void load_weight_bias(neural_net *net);
void save_weight_bias(neural_net *net);

#endif