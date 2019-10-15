#include <stdio.h>
#include <stdlib.h>
#include <err.h>
#include <math.h>







int training[4][2] = {{0, 0}, {0, 1}, {1, 0}, {1, 1} };
int anwser[4] = {0, 1, 1, 0};

int weight[6];

float sigmoid(float x)
{
	return 1/(1 + exp(-x));
}

void generate_weights()
{
	srand(time(NULL));
	for (int i = 0; i < 9; i++)
	{
		int randNum = rand() % 2;
		if (randNum == 1)
			weights[i] = -1 * (double(rand()) / (double(RAND_MAX) + 1.0)); // generate number between -1.0 and 0.0
		else
			weights[i] = double(rand()) / (double(RAND_MAX) + 1.0); // generate number between 1.0 and 0.0

		cout << "weight " << i << " = " << weights[i] << endl;
	}
	cout << "" << endl;
}