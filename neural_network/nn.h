#ifndef NN_H
#define NN_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <err.h>

#define WIDTH_MATRIX 29
#define HEIGHT_MATRIX 29
#define HIDDEN_N 300
#define OUTPUTS 52

typedef struct 
{
    size_t nb_input;
    size_t nb_hidden;
    size_t nb_output;

    double* input_layer;
    double* hidden_layer;
    double* output_logits;
    double* output_activation;

    double* weight_input_hidden;
    double* weight_hidden_output;

    double* bias_hidden;
    double* bias_output;

    double* goal;

    double* cost_array;
    double cost;
    
    double learning_rate;    
} neural_net;

neural_net init_net();
void init_value(neural_net *net);
void neural_network(neural_net *net, char* file);

#endif