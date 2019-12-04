#ifndef TOOLS_H
#define TOOLS_H

#include <math.h>
#include <stdlib.h>
#include "nn.h"

double random(int min, int max);

//ACTIVATION FUNCTIONS AND DERIVATIVE
double sigmoid(double x);
double sigmoid_prime(double x);

//COST FUNCTION
double cost(double* output, double* goal, size_t len);

//MATRICE TOOLS FUNCTIONS
void copy_matrix(double* src, double* dst, size_t len);
void add_matrix(double *src, double *dst, size_t len);
void mul_matrix(double *input, double *weight, double* output,\
                size_t height_input, size_t height_weight);
//void transpose_matrix(double *src, size_t width_src, size_t height_src, double *dst);

//GOAL AND RESULT FUNCTIONS
void make_goal_matrix(double* goal, size_t len, char c);
char get_result(double* output, size_t len);

#endif