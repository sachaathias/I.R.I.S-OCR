#include <stdio.h>
#include <stdlib.h>
#include <err.h>
#include <math.h>
#include <time.h>



int training[4][2] = {{0, 0}, {0, 1}, {1, 0}, {1, 1}};
int anwser[4] = {0, 1, 1, 0};

double weight_hidden[4];
double weight_output[1];
float biases[2];
float error[3];
float output;

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

//initialize random weights 
void initialize_weights()
{
	srand(time(NULL));
	for (int i = 0; i < 6; i++)
	{
		int randNum = rand() % 2;
		if (randNum == 1)
			weights[i] = -1 * (double(rand()) / (double(RAND_MAX) + 1.0)); // generate number between -1.0 and 0.0
		else
			weights[i] = double(rand()) / (double(RAND_MAX) + 1.0); // generate number between 1.0 and 0.0
	}
	
}

void initialize_bias()
{
	srand(time(NULL));
	for (int i = 0; i < 2; i++)
	{
		biases[i] = double(rand()) / (double(RAND_MAX) + 1.0);
	}
}



float cost_function(float weight, float bias)
{
	return 0;

}



