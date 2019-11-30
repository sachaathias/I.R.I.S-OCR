#ifndef TOOLS_H
#define TOOLS_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_SIZE_LINE 1000

double random(int min, int max);
void dot(double *input, size_t height_input,\
         double *weight, size_t height_weight,\
         double *bias, double *output);
void copy(double* src, double* dst, size_t len);
double cost(double* output, double* expected, size_t len);
double cost_derivative(double output, double expected);
void do_sigmoid(double* output, size_t len);
double sigmoid_prime(double x);
void make_goal_matrix(double* goal, size_t len, char c);
char get_result(double* output_a, size_t len);

#endif