#include "nn.h"

neural_net* init_net()
{
    neural_net *net = malloc(sizeof(neural_net));
    net->nb_input = NB_INPUT;
    net->nb_hidden = NB_HIDDEN;
    net->nb_output = NB_OUTPUT;

    net->cost = 0.0;
    net->learning_rate = 0.5;

    for(size_t i = 0; i < net->nb_input; i++)
    {
        for(size_t h = 0; h < net->nb_hidden; h++)
        {
            net->w_IH[h * net->nb_input + i] = random(0, 0);
            net->delta_w_IH[h * net->nb_input + i] = 0.0;
        }
    }

    for(size_t h = 0; h < net->nb_hidden; h++)
    {
        for(size_t o = 0; o < net->nb_output; o++)
        {
            net->w_HO[o * net->nb_hidden + h] = random(0, 0);
            net->delta_w_HO[o * net->nb_hidden + h] = 0.0;
        }
        net->b_H[h] = random(0, 0);
        net->delta_b_H[h] = 0.0;
    }

    for(size_t o = 0; o < net->nb_output; o++)
    {
        net->b_O[o] = random(0, 0);
        net->delta_b_O[o] = 0.0;
    }

    return net;
}

//#############################################################################
//######################### FORWARD PROPAGATION ###############################
//#############################################################################

char forward(neural_net *net, double *input, char expected)
{
    copy_matrix(input, net->input, net->nb_input);
    make_goal_matrix(net->goal, net->nb_output, expected);

    mul_matrix(net->input, net->w_IH, net->hidden, net->nb_input, net->nb_hidden);
    add_matrix(net->b_H, net->hidden, net->nb_hidden);

    for(size_t h = 0; h < net->nb_hidden; h++)
    {
        net->hidden[h] = sigmoid(net->hidden[h]);
    }

    mul_matrix(net->hidden, net->w_HO, net->output, net->nb_hidden, net->nb_output);
    add_matrix(net->b_O, net->output, net->nb_output);

    for(size_t o = 0; o < net->nb_output; o++)
    {
        net->output[o] = sigmoid(net->output[o]);
    }

    net->cost = cost(net->output, net->goal, net->nb_output);

    return get_result(net->output, net->nb_output);
}

//#############################################################################
//######################## BACKWARD PROPAGATION ###############################
//#############################################################################

//Update all the weights
void update_weights(neural_net *net)
{
    double eta = net->learning_rate;
    for(size_t i = 0; i < net->nb_input; i++)
    {
        for(size_t h = 0; h < net->nb_hidden; h++)
        {
            net->w_IH[h * net->nb_input + i] -= eta * net->delta_w_IH[h * net->nb_input + i];
        }
    }

    for(size_t h = 0; h < net->nb_hidden; h++)
    {
        for(size_t o = 0; o < net->nb_output; o++)
        {
            net->w_HO[o * net->nb_output + h] -= eta * net->delta_w_HO[o * net->nb_hidden + h];
        }
    }
}

//Update all the bias
void update_bias(neural_net *net)
{
    double eta = net->learning_rate;
    for(size_t h = 0; h < net->nb_hidden; h++)
    {
        net->b_H[h] -= eta * net->delta_b_H[h];
    }

    for(size_t o = 0; o < net->nb_output; o++)
    {
        net->b_O[o] -= eta * net->delta_b_O[o];
    }
}

//Backpropagation
void backward(neural_net *net)
{
    for(size_t o = 0; o < net->nb_output; o++)
    {
        net->delta_b_O[o] = (net->output[o] - net->goal[o]) * sigmoid_prime(net->output[o]);
    }

    for(size_t h = 0; h < net->nb_hidden; h++)
    {
        double sum = 0.0;
        /*double *trp_w = malloc(sizeof(double) * net->nb_hidden * net->nb_output);
        transpose_matrix(net->w_HO, net->nb_hidden, net->nb_output, trp_w);*/
        for(size_t o = 0; o < net->nb_output; o++)
        {
            sum += net->delta_b_O[o] * net->w_HO[o * net->nb_hidden + h];

            net->delta_w_HO[o * net->nb_hidden + h] = net->hidden[h] * net->delta_b_O[o];
        }
        net->delta_b_H[h] = sum * sigmoid_prime(net->hidden[h]);
    }

    for(size_t i = 0; i < net->nb_input; i++)
    {
        for(size_t h = 0; h < net->nb_hidden; h++)
        {
            net->delta_w_IH[h * net->nb_hidden + i] = net->input[i] * net->delta_b_H[h];
        }
    }
}