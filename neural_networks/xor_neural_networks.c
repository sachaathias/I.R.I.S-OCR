#include <stdio.h>
#include <stdlib.h>
#include <err.h>
#include <math.h>
#include <time.h>
#include "xor_neural_networks.h"



int training[4][2] = {{0, 0}, {0, 1}, {1, 0}, {1, 1}};
int anwser[4] = {0, 1, 1, 0};

struct Network
{
//number of inputs and number of neurons in hidden layer
	int inputs;
	int hidden;
//arrays of weights and biases
	double *weight_hidden;
	double *weight_output;
	double *biases_hidden;
	double bias_output;
//output of hidden layer
	double *output_hidden;
//error rate and output of the network
	float error;
	float output;
//training data
	int *training;
//network goal anwser
	int *anwser;
}


//the sigmoid function
float sigmoid(float x)
{
	return 1/(1 + exp(-x));
}

//the derivative of the sigmoid function
float sigmoid_derivative(float x)
{
	return exp(-x)/pow((1 + exp(-x), 2));
}

//initialize the struct and allocate the memory
struct Initialize_network()
{
	struct Network self;
	self.inputs = 2;
	self.hidden = 3;
	self.weight_hidden = malloc(sizeof(double)*self.inputs*self.hidden);
	self.weight_output = malloc(sizeof(double)*self.hidden);
	self.biases_hidden = malloc(sizeof(double)*self.hidden);
	self.bias_output = (double)rand()/(double)RAND_MAX;
	self.output_hidden = malloc(sizeof(double)*self.hidden);
	self.error = 0.0;
	self.output = 0.0;
	self.training = malloc(sizeof(int)*4*2);
	self.anwser = malloc(sizeof(int)*4);






}
