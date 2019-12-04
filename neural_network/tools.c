#include "tools.h"

inline double random(int min, int max)
{
    if(min == 0 && max == 0)
        return (double)rand()/((double)RAND_MAX / 2) - 1;
    return (double)(rand() % (max - min + 1) + min);
}

//#############################################################################
//################ ACTIVATION FUNCTIONS AND DERIVATIVE ########################
//#############################################################################

inline double sigmoid(double x)
{
    return 1.0/(1.0+exp(-x));
}

inline double sigmoid_prime(double x)
{
    return x*(1.0 - x);
}

//#############################################################################
//########################### COST FUNCTION ###################################
//#############################################################################

//Quadratic cost function
double cost(double* output, double* goal, size_t len)
{
    double max = 0;
    double s = 0;

    for(size_t o = 0; o < len; o++)
    {
        if(max < output[o])
            max = output[o];
        s += (output[o] - goal[o]) * (output[o] - goal[o]);
    }
    return s;
}

//#############################################################################
//######################## MATRICE TOOLS FUNCTIONS ############################
//#############################################################################

//Copy src arrray into dst array
void copy_matrix(double* src, double* dst, size_t len)
{
    for(size_t i = 0; i < len; i++)
    {
        dst[i] = src[i];
    }
}

//Add matrix src to dst (they have the same length)
void add_matrix(double *src, double *dst, size_t len)
{
    for(size_t i = 0; i < len; i++)
    {
        dst[i] += src[i];
    }
}

//Multiply weight with input into output
void mul_matrix(double *input, double *weight, double* output,\
                size_t height_input, size_t height_weight)
{
    for(size_t i = 0; i < height_input; i++)
    {
        for(size_t h = 0; h < height_weight; h++)
        {
            output[h] += input[i] * weight[h * height_input + i];
        }
    }
}

//Transpose src into dst
/*void transpose_matrix(double *src, size_t width_src, size_t height_src, double *dst)
{
    for(size_t i = 0; i < width_src; i++)
    {
        for(size_t j = 0; j < height_src; j++)
        {
            dst[i * height_src + j] = src[j * width_src + i];
        }
    }
}*/

//#############################################################################
//###################### GOAL AND RESULT FUNCTIONS ############################
//#############################################################################

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
char get_result(double* output, size_t len)
{
    int max = 0;
    double max_value = 0.0;

    for(size_t i = 0; i < len; i++)
    {
        if(output[i] > max_value)
        {
            max = i;
            max_value = output[i];
        }
    }

    if(max >= 0 && max <= 25)
        return (char)(max + 65);
    else
        return (char)(max + 97 - 26);
}