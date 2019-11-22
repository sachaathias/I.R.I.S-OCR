#include "nn.h"

double random()
{
    return (double)rand()/(double)RAND_MAX;
}

//Return a constant for softmax function to avoid nan
double const_softmax(neural_net *net)
{
    double max = 0;
    for(size_t i = 0; i < net->nb_output; i++)
    {
        if(net->output_logits[i] > max)
            max = net->output_logits[i];
    }
    return -max;
}

neural_net init_net()
{
    neural_net net;

    net.nb_input = WIDTH_MATRIX*HEIGHT_MATRIX;
    net.nb_hidden = HIDDEN_N;
    net.nb_output = OUTPUTS;

    net.input_layer = malloc(sizeof(double)*net.nb_input);
    net.hidden_layer = malloc(sizeof(double)*net.nb_hidden);
    net.output_logits = malloc(sizeof(double)*net.nb_output);
    net.output_activation = malloc(sizeof(double)*net.nb_output);

    net.weight_input_hidden = malloc(sizeof(double)*net.nb_input*net.nb_hidden);
    net.weight_hidden_output = malloc(sizeof(double)*net.nb_hidden*net.nb_output);

    net.bias_hidden = malloc(sizeof(double)*net.nb_hidden);
    net.bias_output = malloc(sizeof(double)*net.nb_output);

    net.delta_output = malloc(sizeof(double)*net.nb_output);
    net.delta_hidden = malloc(sizeof(double)*net.nb_hidden);

    net.goal = malloc(sizeof(double)*net.nb_output);

    net.cost_array = malloc(sizeof(double)*net.nb_output);
    net.cost = 0.0;

    net.learning_rate = 0.05;

    return net;
}

void init_value(neural_net *net)
{
    for(size_t i = 0; i < net->nb_input; i++)
    {
        for(size_t h = 0; h < net->nb_hidden; h++)
        {
            net->weight_input_hidden[h + i * net->nb_hidden] = random();
        }
    }

    for (size_t h = 0; h < net->nb_hidden; h++)
    {
        net->bias_hidden[h] = random();
        net->delta_hidden[h] = 0.0;
        for(size_t o = 0; o < net->nb_output; o++)
        {
            net->weight_hidden_output[o + h * net->nb_output] = random();
            if(h == 0)
            {
                net->bias_output[o] = random();
                net->delta_output[o] = 0.0;
            }
        }
    }
}

void set_input(neural_net* net, double* input)
{
    for(size_t i = 0; i < net->nb_input; i++)
    {
        net->input_layer[i] = input[i];
    }
}

double* goal_array(neural_net *net, char c)
{
    double* goal = calloc(net->nb_output, sizeof(double));

    if(c >= 'A' && c <= 'Z')
        *(goal + (int)c - 65) = 1;
    else if(c >= 'a' && c <= 'z')
        *(goal + (int)c - 97 + 26) = 1;
    return goal;
}

void set_goal(neural_net* net, char c)
{
    double* goal = goal_array(net, c);
    for(size_t o = 0; o < net->nb_output; o++)
    {
        net->goal[o] = (double)goal[o];
    }
}

char get_result(neural_net *net)
{
    double max = 0;
    int posMax = 0;

    //Get Max value
    for(size_t o = 0; o < net->nb_output; o++)
    {
        if(max < net->output_activation[o])
        {
            max = net->output_activation[o];
            posMax = o;
        }
    }

    char c;
    //Upper
    if(posMax <= 25)
        c = posMax + 65;
    //Lower
    else if(posMax > 25 && posMax <= 51)
        c = posMax + 97 - 26;
    return c;
}
/*
void cost(neural_net *net)//Quadratique
{
    double output, goal, cost;
    double total_cost = 0.0
    ;
    for(size_t o = 0; o < net->nb_output; o++)
    {
        output = net->output_activation[o];
        goal = net->goal[o];
        cost = (output - goal) * (output - goal);
        net->cost_array[o] = cost;
        total_cost += cost;
    }
    net->cost = total_cost;
}
*/

void print_output_layers(neural_net *net)
{
    for(size_t o = 0; o < net->nb_output; o++)
    {
        printf("%f -- %f | %f\n", net->goal[o], net->output_activation[o], net->output_logits[o]);
    }
}

//Cross entropy loss
void cost(neural_net *net)
{
    double sum = 0.0;
    for(size_t o = 0; o < net->nb_output; o++)
    {
        sum += (net->goal[o] * log(net->output_activation[o] + exp(-8)));
    }
    net->cost = -sum;
}

void softmax(neural_net* net)
{
    double sum_exp = 0.0;
    double cst = const_softmax(net);

    for(size_t o = 0; o < net->nb_output; o++)
    {
        sum_exp += exp(net->output_logits[o] + cst);
    }
    for(size_t o = 0; o < net->nb_output; o++)
    {
        net->output_activation[o] = exp(net->output_logits[o] + cst) / sum_exp;
    }
}

double relu(double n)
{
    if(n < 0)
        return 0;
    return n;
}

//Forward propagation
char forward(neural_net* net)
{
    double sum;

    //Input to hidden layer
    for(size_t h = 0; h < net->nb_input; h++)
    {
        sum =  net->bias_hidden[h];
        for(size_t i = 0; i < net->nb_hidden; i++)
        {
            sum += net->input_layer[i] * net->weight_input_hidden[h + i * net->nb_hidden];
        }
        net->hidden_layer[h] = relu(sum);
    }

    //Hidden to output (logits) layer
    for(size_t o = 0; o < net->nb_output; o++)
    {
        sum = net->bias_output[o];
        for (size_t h = 0; h < net->nb_hidden; h++)
        {
            sum += net->hidden_layer[h] * net->weight_hidden_output[o + h * net->nb_output];
        }
        net->output_logits[o] = sum;
    }
    softmax(net);
    cost(net);

    return get_result(net);
}

void backward(neural_net *net)
{
    //Output to hidden
    for(size_t o = 0; o < net->nb_output; o++)
    {
        double delta = net->output_activation[o] - net->goal[o];
        for(size_t h = 0; h < net->nb_hidden; h++)
        {
            net->weight_hidden_output[o + h * net->nb_output] -=
                (delta * net->hidden_layer[h] * net->learning_rate);
        }
        net->bias_output[o] -= delta;
        net->delta_output[o] = delta;
    }
    
}

void neural_network(neural_net *net, matrix* mat, char c)
{
    set_input(net, mat->data);
    set_goal(net, c);

    char r = forward(net);
    backward(net);
    print_output_layers(net);
    printf("Result: %c | Expected: %c\nCost: %f\n", r, c, net->cost);
}

