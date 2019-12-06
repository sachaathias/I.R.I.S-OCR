#ifndef TOOLS_H
#define TOOLS_H

#include <math.h>
#include <stdlib.h>
#include <stdlib.h>

double random(int min, int max);

//ACTIVATION FUNCTIONS
double sigmoid(double x);
double sigmoid_prime(double x);

//COST FUNCTION
double cost(double* output, double *goal, size_t len);

//MATRICE AND TOOLS FUNCTIONS
void copy_matrix(double* src, double* dst, size_t len);

//GOAL AND RESULT FUNCTIONS
void make_goal_matrix(double* goal, size_t len, char c);
char get_result(double* output, size_t len);

#endif