#include "tools.h"

//return a random number
inline double random(int min, int max)
{
    if(min == -1 && max == 1)
    {
        double r = (double)rand();
        return pow(-1, r)*(r/(double)RAND_MAX);
    }
    return (double)(rand() % (max - min + 1) + min);
}

//output = sum(input*weight) + bias
void dot(double *input, size_t height_input,\
         double *weight, size_t height_weight,\
         double *bias, double *output)
{
    for(size_t i = 0; i < height_weight; i++)
    {
        output[i] = bias[i];
        for(size_t j = 0; j < height_input; j++)
        {
            output[i] += input[j] * weight[i * height_input + j];
        }
    }
}

//Copy src arrray into dst array
void copy(double* src, double* dst, size_t len)
{
    for(size_t i = 0; i < len; i++)
    {
        dst[i] = src[i];
    }
}

/*//Cross entropy loss
void cost(neural_net *net)
{
    double sum = 0.0;
    for(size_t o = 0; o < net->nb_output; o++)
    {
        sum += (net->goal[o] * log(net->output_activation[o]));
    }
    net->cost = -sum;
}*/

//Cost (log-likelihood)
double cost(double* output, double* expected, size_t len)
{
    double cost = 0.0;
    for(size_t i = 0; i < len; i++)
    {
        cost += ((expected[i] - output[i]) * (expected[i] - output[i]));
    }
    return cost / (2*len);
}

double cost_derivative(double output, double expected)
{
    return (expected - output);
}

//Sigmoid activation functio
static inline double sigmoid(double x)
{
    return 1.0/(1.0+exp(-x));
}

//Derivative of sigmoid
inline double sigmoid_prime(double x)
{
    return x*(1-x);
}

//Do sigmoid on a list
void do_sigmoid(double* output, size_t len)
{
    for(size_t i = 0; i < len; i++)
    {
        output[i] = sigmoid(output[i]);
    }
}

//Return a constant for softmax function to avoid nan
double const_softmax(double* list, size_t len)
{
    double max = 0;
    for(size_t i = 0; i < len; i++)
    {
        if(list[i] > max)
            max = list[i];
    }
    return -max;
}

void softmax(double* list, size_t len)
{
    double sum_exp = 0.0;
    double cst = const_softmax(list, len);

    for(size_t o = 0; o < len; o++)
    {
        sum_exp += exp(list[o] + cst);
    }
    for(size_t o = 0; o < len; o++)
    {
        list[o] = exp(list[o] + cst) / sum_exp;
    }
}

//Create a goal matrix corresponding to the expected output
void make_goal_matrix(double* goal, size_t len, char c)
{
    for(size_t i = 0; i < len; i++)
        goal[i] = 0.0;
    
    if(c >= 'A' && c <= 'Z')
        goal[c - 65] = 1;
    else
        goal[c - 97 + 26] = 1;
}

//Return the char which correspond to the output
char get_result(double* output_a, size_t len)
{
    int max = 0;
    double max_value = 0.0;

    for(size_t i = 0; i < len; i++)
    {
        if(output_a[i] > max_value)
        {
            max = i;
            max_value = output_a[i];
        }
    }

    if(max >= 0 && max <= 25)
        return (char)(max + 65);
    else
        return (char)(max + 97 - 26);
}
