#include "tools.h"

inline double random()
{
    return ((double)rand()) / ((double)RAND_MAX / 2) - 1;
}

//#############################################################################
//###################### ACTIVATION FUNCTIONS #################################
//#############################################################################

inline double sigmoid(double x)
{
    return 1.0/(1.0+exp(-x));
}

inline double sigmoid_prime(double x)
{
    return x*(1-x);
}

//#############################################################################
//######################### COST FUNCTION #####################################
//#############################################################################

double cost(double output[], double goal[], size_t len)
{
    double cost = 0.0;

    for(size_t i = 0; i < len; i++)
    {
        cost += (goal[i] - output[i]) * (goal[i] - output[i]);
    }

    return 0.5 * cost;
}

//#############################################################################
//######################## MATRICE TOOLS FUNCTIONS ############################
//#############################################################################

//Copy src arrray into dst array
void copy_matrix(double src[], double dst[], size_t len)
{
    for(size_t i = 0; i < len; i++)
    {
        dst[i] = src[i];
    }
}

//#############################################################################
//###################### GOAL AND RESULT FUNCTIONS ############################
//#############################################################################

//Create a goal matrix corresponding to the expected output
void make_goal_matrix(double goal[], size_t len, char c)
{
    for(size_t i = 0; i < len; i++)
        goal[i] = 0.0;

    /*if(c >= 'A' && c <= 'Z')
        goal[c - 65] = 1.0;
    else if(c >= 'a' && c <= 'z')
        goal[c - 97 + 26] = 1.0;
    else if(c >= '0' && c <= '9')
	goal[c] = 1.0;*/
    if(c >= '0' && c <= '9')
	goal[c - 48] = 1.0;
    else if(c >= 'A' && c <= 'Z')
	goal[c - 65 + 10] = 1.0;
    else/* if(c >= 'a' && c <= 'z')*/
	goal[c - 97 + 36] = 1.0;
}

//Return the char which correspond to the output
char get_result(double output[], size_t len)
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

    /*if(max >= 0 && max <= 25)
        return (char)(max + 65);
    else
        return (char)(max + 97 - 26);*/
    if(max >= 0 && max <= 9)
	return (char)(max + 48);
    else if(max >= 10 && max <= 35)
	return (char)(max + 65 - 10);
    else/* if(max >= 36 && max <= 61)*/
	return (char)(max + 97 - 36);
}
