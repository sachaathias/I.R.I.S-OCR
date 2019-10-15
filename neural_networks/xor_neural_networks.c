#include <stdio.h>
#include <stdlib.h>
#include <err.h>
#include <math.h>
#include <time.h>



int training[4][2] = {{0, 0}, {0, 1}, {1, 0}, {1, 1}};
int anwser[4] = {0, 1, 1, 0};

int weight[6];
int bias[2];

float sigmoid(float x)
{
	return 1/(1 + exp(-x));
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
		bias[i] = double(rand()) / (double(RAND_MAX) + 1.0);
	}
}

