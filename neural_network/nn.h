#ifndef NN_H
#define NN_H

#include <stdlib.h>
#include "tools.h"

#define NB_INPUT 28*28
#define NB_HIDDEN 100
#define NB_OUTPUT 62

typedef struct
{
    size_t nb_input;
    size_t nb_hidden;
    size_t nb_output;

    double input[NB_INPUT];
    double hidden[NB_HIDDEN];
    double output[NB_OUTPUT];

    double w_IH[NB_INPUT][NB_HIDDEN];
    double w_HO[NB_HIDDEN][NB_OUTPUT];

    double b_H[NB_HIDDEN];
    double b_O[NB_OUTPUT];

    double delta_H[NB_HIDDEN];
    double delta_O[NB_OUTPUT];

    double delta_w_IH[NB_INPUT][NB_HIDDEN];
    double delta_w_HO[NB_HIDDEN][NB_OUTPUT];

    double goal[NB_OUTPUT];

    double cost;
    double eta;
} neural_net;

neural_net* init_net();

//FORWARD PROPAGATION
char forward(neural_net *net, double *input, char expected);

//BACK PROPAGATION
void backward(neural_net *net);
void update_weights_bias(neural_net* net);

#endif
