#include "nn.h"

#include <stdio.h>



neural_net* init_net()
{
    neural_net *net = malloc(sizeof(neural_net));
    net->nb_input = NB_INPUT;
    net->nb_hidden = NB_HIDDEN;
    net->nb_output = NB_OUTPUT;

    net->cost = 0.0;
    net->eta = 0.3;

    for(size_t i = 0; i < net->nb_input; i++)
    {
        for(size_t h = 0; h < net->nb_hidden; h++)
        {
            net->w_IH[i][h] = random();
            net->delta_w_IH[i][h] = 0.0;
        }
    }

    for(size_t h = 0; h < net->nb_hidden; h++)
    {
        for(size_t o = 0; o < net->nb_output; o++)
        {
            net->w_HO[h][o] = random();
            net->delta_w_HO[h][o] = 0.0;
        }
        net->b_H[h] = random();
        net->delta_H[h] = 0.0;
    }

    for(size_t o = 0; o < net->nb_output; o++)
    {
        net->b_O[o] = random();
        net->delta_O[o] = 0.0;
    }

    return net;
}

//#############################################################################
//######################### FORWARD PROPAGATION ###############################
//#############################################################################

char forward(neural_net *net, double *input, char expected)
{
    //Initialize input and goal (for training)
    copy_matrix(input, net->input, net->nb_input);

    if(expected != 0)
    	make_goal_matrix(net->goal, net->nb_output, expected);

    //Propagation between input and hidden layer
    for(size_t h = 0; h < net->nb_hidden; h++)
    {
        net->hidden[h] = net->b_H[h];
        for (size_t i = 0; i < net->nb_input; i++)
        {
            net->hidden[h] += net->w_IH[i][h] * net->input[i];
        }
        net->hidden[h] = sigmoid(net->hidden[h]);
    }

    //Propagation between hidden and output layer
    for(size_t o = 0; o < net->nb_output; o++)
    {
        net->output[o] = net->b_O[o];
        for(size_t h = 0; h < net->nb_hidden; h++)
        {
            net->output[o] += net->w_HO[h][o] * net->hidden[h];
        }
        net->output[o] = sigmoid(net->output[o]);
    }

    //Calculate cost
    if(expected != 0)
    	net->cost = cost(net->output, net->goal, net->nb_output);
    else
	    net->cost = 0;

    return get_result(net->output, net->nb_output);
}

//#############################################################################
//############################ BACK PROPAGATION ###############################
//#############################################################################

void backward(neural_net *net)
{
    //Calculate deltas for output layer
    for(size_t o = 0; o < net->nb_output; o++)
    {
        net->delta_O[o] = sigmoid_prime(net->output[o]) * (net->goal[o] - net->output[o]);
    }

    //Calculate deltas for hidden layer
    for(size_t h = 0; h < net->nb_hidden; h++)
    {
        net->delta_H[h] = 0.0;
        for(size_t o = 0; o < net->nb_output; o++)
        {
            net->delta_H[h] += net->delta_O[o] * net->w_HO[h][o];
        }
        net->delta_H[h] *= sigmoid_prime(net->hidden[h]);
    }
}

void update_weights_bias(neural_net* net)
{
    //Update weights and bias for output layer
    for(size_t o = 0; o < net->nb_output; o++)
    {
        net->b_O[o] += net->eta * net->delta_O[o];
        for(size_t h = 0; h < net->nb_hidden; h++)
        {
            double delta =  net->eta * net->hidden[h] * net->delta_O[o];
            net->w_HO[h][o] += delta + net->delta_w_HO[h][o];
            net->delta_w_HO[h][o] = delta;
        }
    }

    //Update weights and bias for hidden layer
    for (size_t h = 0; h < net->nb_hidden; h++)
    {
        net->b_H[h] += net->eta * net->delta_H[h];
        for (size_t i = 0; i < net->nb_input; i++)
        {
            double delta = net->eta * net->input[i] * net->delta_H[h];
            net->w_IH[i][h] += delta + net->delta_w_IH[i][h];
            net->delta_w_IH[i][h] = delta;
        }        
    }
}
