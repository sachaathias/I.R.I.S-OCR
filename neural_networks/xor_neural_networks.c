#include <stdio.h>
#include <stdlib.h>
#include <err.h>
#include <math.h>
#include <time.h>
#include "xor_neural_networks.h"

//prototypes
struct Network;
double Random();
float sigmoid(float x);
float sigmoid_derivative(float x);
struct Initalize_network();
void Init_value(struct Network *self);
float feedforward();


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
//delta of weights
	double *dweight_hidden;
	double *dweight_output;
//delta of biases
	double *dbiases_hidden;
	double dbias_output;
//delta output
	float doutput;
//training data(inputs)
	int *training;
//network goal anwser
	int *anwser;
}

/*----------------Tool functions--------------*/

//return a random
double Random()
{
    return (double)rand()/(double)RAND_MAX;
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

/*----------------Initialize Network-----------*/

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
	return self;
}

void Init_value(struct Network *self)
{
  *((*self).training) = 0;
  *((*self).training +1) = 0;
  *((*self).training +2) = 0;
  *((*self).training +3) = 1;
  *((*self).training +4) = 1;
  *((*self).training +5) = 0;
  *((*self).training +6) = 1;
  *((*self).training +7) = 1;
  
  *((*self).anwser) = 0;
  *((*self).anwser +1) = 1;
  *((*self).anwser +2) = 1;
  *((*self).anwser +3) = 0;

  for(int i = 0; i < (*self).inputs; i++)
  {
	  for(int j = 0; j < (*self).hidden; j++)
	  {
		*((*self).weight_hidden + (j+i * (*self).hidden)) = Random();
		*((*self).dweight_hidden + (j+i * (*self).hidden))=0.0;
	  }
  }

  for(int i = 0; i < (*self).hidden; ++i)
  {
	  *((*self).weight_output + i) = Random();
	  *((*self).dweight_output + i) = 0.0;
	  *((*self).biases_hidden + i) = Random();
	  *((*self).dbiases_hidden + i) = 0.0;
  }
  (*self).dbiases_output = 0.0;
}

float feedforward(struct Network *self)
{
	for(int i = 0; i < (*self).weight_hidden; i++)
	{


	
}


