#include "nn.h"

//Create and initialize a neural net and return it
neural_net* init_net()
{
    neural_net *net = malloc(sizeof(neural_net));
    net->nb_input = NB_INPUT;
    net->nb_hidden = NB_HIDDEN;
    net->nb_output = NB_OUTPUT;

    net->cost = 0.0;
    net->learning_rate = 0.5;
    net->alpha = 0.6;

    for(size_t i = 0; i < net->nb_input; i++)
    {
        for(size_t h = 0; h < net->nb_hidden; h++)
        {
            net->w_IH[i * net->nb_hidden + h] = random(-1, 1);
            net->delta_w_IH[i * net->nb_hidden + h] = 0.0;
        }
    }

    for(size_t h = 0; h < net->nb_hidden; h++)
    {
        for(size_t o = 0; o < net->nb_output; o++)
        {
            net->w_HO[h * net->nb_output + o] = random(-1, 1);
            net->delta_w_HO[h * net->nb_output + o] = 0.0;
        }
        net->b_H[h] = random(-1, 1);
        net->delta_b_H[h] = 0.0;
    }

    for(size_t o = 0; o < net->nb_output; o++)
    {
        net->b_O[o] = random(-1, 1);
        net->delta_b_O[o] = 0.0;
    }

    return net;
}

//Forward propagation
//tab[i][j] --> i ligne / j colonne
char forward(neural_net* net, double* input, char expected)
{
    copy(input, net->input, net->nb_input);
    make_goal_matrix(net->goal, net->nb_output, expected);

    dot(net->input, net->nb_input, net->w_IH,\
        net->nb_hidden, net->b_H, net->hidden);

    do_sigmoid(net->hidden, net->nb_hidden);

    dot(net->hidden, net->nb_hidden, net->w_HO,\
        net->nb_output, net->b_O, net->output);


    softmax(net->output, net->nb_output);

    net->cost = cost(net->output, net->goal, net->nb_output);

    return get_result(net->output, net->nb_output);
}

void update_weights(neural_net* net)
{
    double eta = net->learning_rate;

    for(size_t h = 0; h < net->nb_hidden; h++)
    {
        for(size_t i = 0; i < net->nb_input; i++)
        {
            net->w_IH[i * net->nb_hidden + h] += eta * net->delta_b_H[h] * net->input[i]
                                                + net->alpha * net->delta_w_IH[i * net->nb_hidden + h];
            net->delta_w_IH[i * net->nb_hidden + h] = eta * net->delta_b_H[h] * net->input[i];
        }
    }

    for(size_t o = 0; o < net->nb_output; o++)
    {
        for(size_t h = 0; h < net->nb_hidden; h++)
        {
            net->w_HO[h * net->nb_output + o] += net->delta_w_HO[h * net->nb_output + o];
        }
    }
}

void update_biases(neural_net* net)
{
    double eta = net->learning_rate;

    for(size_t h = 0; h < net->nb_hidden; h++)
    {
        net->b_H[h] += eta * net->delta_b_H[h];
    }

    for(size_t o = 0; o < net->nb_output; o++)
    {
        net->b_O[o] += net->delta_b_O[o];
    }
}

void backward(neural_net* net)
{
    double eta = net->learning_rate;
    double sum;
    for(size_t h = 0; h < net->nb_hidden; h++)
    {
        sum = 0.0;
        for(size_t o = 0; o < net->nb_output; o++)
        {
            sum += (net->delta_b_O[o] * net->w_HO[h * net->nb_output + o]);
        }
        net->delta_b_H[h] = (sum * sigmoid_prime(net->hidden[h]));
    }

    for(size_t o = 0; o < net->nb_output; o++)
    {
        net->delta_b_O[o] = -eta * (net->output[o] - net->goal[o]);
    }

    for(size_t o = 0; o < net->nb_output; o++)
    {
        for(size_t h = 0; h < net->nb_hidden; h++)
        {
            net->delta_w_HO[h * net->nb_output + o] = -eta * net->hidden[h] * net->delta_b_O[o];
        }
    }
}

void load_weight_bias(neural_net* net)
{
    /*
    WEIGHT_INPUT_HIDDEN
    WEIGHT_HIDDEN_OUTPUT
    BIAS_HIDDEN
    BIAS_OUTPUT
    */
    FILE* file = NULL;
    file = fopen("netvalue.nn", "r");

    if(file != NULL)
    {
        char str[MAX_SIZE_LINE] = "";
        //WEIGHT_INPUT_HIDDEN
        for(size_t i = 0; i < net->nb_input; i++)
        {
            for(size_t h = 0; h < net->nb_hidden; h++)
            {
                fgets(str, MAX_SIZE_LINE, file);
                *(net->w_IH + (h + i * net->nb_hidden)) = atof(str);
            }
        }

        //WEIGHT_HIDDEN_OUTPUT
        for(size_t h = 0; h < net->nb_hidden; h++)
        {
            for(size_t o = 0; o < net->nb_output; o++)
            {
                fgets(str, MAX_SIZE_LINE, file);
                *(net->w_HO + (o + h * net->nb_output)) = atof(str);
            }
        }

        //BIAS_HIDDEN
        for(size_t h = 0; h < net->nb_hidden; h++)
        {
            fgets(str, MAX_SIZE_LINE, file);
            *(net->b_H + h) = atof(str);
        }

        //BIAS_OUTPUT
        for(size_t o = 0; o < net->nb_output; o++)
        {
            fgets(str, MAX_SIZE_LINE, file);
            *(net->b_O + o) = atof(str);
        }

        fclose(file);
    }
    /*else
    {
        errx(1, "File is NULL");
    }*/
}

void save_weight_bias(neural_net* net)
{
    /*
    WEIGHT_INPUT_HIDDEN
    WEIGHT_HIDDEN_OUTPUT
    BIAS_HIDDEN
    BIAS_OUTPUT
    */
    FILE* file = NULL;
    file = fopen("netvalue.nn", "w");

    if(file != NULL)
    {
        //WEIGHT_INPUT_HIDDEN
        for(size_t i = 0; i < net->nb_input; i++)
        {
            for(size_t h = 0; h < net->nb_hidden; h++)
            {
                fprintf(file, "%f\n", *(net->w_IH + (h + i * net->nb_hidden)));
            }
        }

        //WEIGHT_HIDDEN_OUTPUT
        for(size_t h = 0; h < net->nb_hidden; h++)
        {
            for(size_t o = 0; o < net->nb_output; o++)
            {
                fprintf(file, "%f\n", *(net->w_HO + (o + h * net->nb_output)));
            }
        }

        //BIAS_HIDDEN
        for(size_t h = 0; h < net->nb_hidden; h++)
        {
            fprintf(file, "%f\n", *(net->b_H + h));
        }

        //BIAS_OUTPUT
        for(size_t o = 0; o < net->nb_output; o++)
        {
            fprintf(file, "%f", *(net->b_O + o));
            if(o < net->nb_output - 1)
                fprintf(file, "\n");
        }

        fclose(file);
    }
    else
    {
        errx(1, "File is NULL");
    }
}
