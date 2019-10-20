#include "nn_xor.h"

//Creation of a type for a neural network
typedef struct
{
	int nb_input;
	int nb_hidden;

	//Values of each layer
	double *input_value;
	double *hidden_value;
	double output_value;

	//Biais of each layer
	double *bias_hidden;
	double bias_output;

	//Use for error_rate and learning
	double *goal_output;

	//Weight of each transitions between two layers
	double *weight_input_hidden;
	double *weight_hidden_output;

	double error_rate;

	double learning_rate;
} neural_net;

//Return a random number
double random()
{
	return (double)rand()/(double)RAND_MAX;
}

//Create a neural net for xor
neural_net init_net()
{
	neural_net net;

	net.nb_input = 2;
	net.nb_hidden = 2;

	net.input_value = malloc(sizeof(double) * net.nb_input * 4);
	net.hidden_value = malloc(sizeof(double) * net.nb_hidden);
	net.output_value = 0.0;

	net.bias_hidden = malloc(sizeof(double) * net.nb_hidden);
	net.bias_output = 0.0;

	net.goal_output = malloc(sizeof(double) * 4);

	net.weight_input_hidden = malloc(sizeof(double) * net.nb_input * net.nb_hidden);
	net.weight_hidden_output = malloc(sizeof(double) * net.nb_hidden);

	net.error_rate = 0.0;

	net.learning_rate = 0.01;

	return net;
}

//Initialize the value of a neural net
void init_value(neural_net *net)
{
	*(net->input_value) = 0;
	*(net->input_value + 1) = 0;
	*(net->input_value + 2) = 0;
	*(net->input_value + 3) = 1;
	*(net->input_value + 4) = 1;
	*(net->input_value + 5) = 0;
	*(net->input_value + 6) = 1;
	*(net->input_value + 7) = 1;

	*(net->goal_output) = 0;
	*(net->goal_output + 1) = 1;
	*(net->goal_output + 2) = 1;
	*(net->goal_output + 3) = 0;

	for(int i = 0; i < net->nb_input; i++)
	{
		for(int h = 0; h < net->nb_hidden; h++)
		{
			*(net->weight_input_hidden + (h + i * net->nb_hidden)) = random();
		}
	}

	for(int h = 0; h < net->nb_hidden; h++)
	{
		*(net->weight_hidden_output + h) = random();
		*(net->bias_hidden + h) = random();
	}
	net->bias_output = random();
}

//Return the Sigmoid of a number
double sigmoid(double x)
{
	return 1/(1+exp(-x));
}

double sigmoid_d(double x)
{
	//return exp(-x) / ((1 + exp(-x)) * (1 + exp(-x)));
	return x * (1.0 - x);
}

//Return the error rate
double error_rate(double expected_output, double output)
{
	//return 0.5 * (expected_output - output) * (expected_output - output);
	return sigmoid(output) * (expected_output - output);
}

//Forward propagation for neural net
void feed_forward(neural_net *net, int p, int print)
{
	for(int i = 0; i < net->nb_input; i++)
	{
		double sum_hidden = 0.0;
		for(int h = 0; h < net->nb_hidden; h++)
		{
			sum_hidden += *(net->input_value + 2 * p  + i) *
			*(net->weight_input_hidden + (h + i * net->nb_hidden));
		}
		*(net->hidden_value + i) = sigmoid(sum_hidden + *(net->bias_hidden + i));
	}

	double sum_output = 0.0;
	for(int h = 0; h < net->nb_hidden; h++)
	{
		sum_output += *(net->hidden_value + h) * *(net->weight_hidden_output + h);
	}
	net->output_value = sigmoid(sum_output + net->bias_output);

	net->error_rate = error_rate(*(net->goal_output + p), net->output_value);

	if(print % 100 == 0)
	{
		printf("%f XOR %f = %f\n", *(net->input_value + 2 * p),
					*(net->input_value + 2 * p + 1),
					net->output_value);
		printf("\tError rate = %f\n\n", net->error_rate);
	}
}

//Backward propagation (learning) for neural net
void backward_propagation(neural_net *net, int p)
{
	//Update weight of hidden to output layer
	*(net->weight_hidden_output) += net->error_rate
		* net->learning_rate * *(net->hidden_value);
	*(net->weight_hidden_output + 1) += net->error_rate
		* net->learning_rate * *(net->hidden_value + 1);
	//Update bias of output layer
	net->bias_output += net->error_rate * net->learning_rate;

	//Calculate error for each hidden neuron
	double e1 = sigmoid_d(*(net->hidden_value))
		* net->error_rate * *(net->weight_hidden_output);
	double e2 = sigmoid_d(*(net->hidden_value + 1))
		* net->error_rate * *(net->weight_hidden_output + 1);
	

	//Adjust weight of neurons
	*(net->weight_input_hidden) += e1 * *(net->input_value + 2 * p) * net->learning_rate;
	*(net->weight_input_hidden + 1) += e1 * *(net->input_value + 2 * p + 1) * net->learning_rate;
	*(net->weight_input_hidden + 2) += e2 * *(net->input_value + 2 * p) * net->learning_rate;
	*(net->weight_input_hidden + 3) += e2 * *(net->input_value + 2 * p + 1) * net->learning_rate;

	//Adjust bias
	*(net->bias_hidden) += e1 * net->learning_rate;
	*(net->bias_hidden + 1) += e2 * net->learning_rate;
}

//Main function of XOR neural net
void XOR()
{
	srand(time(NULL));
	
	int trainMax = 100000000;
	neural_net n = init_net();
	neural_net *net = &n;
	init_value(net);

	*(net->weight_input_hidden) = 20;
	*(net->weight_input_hidden + 1) = 20;
	*(net->weight_input_hidden + 2) = -20;
	*(net->weight_input_hidden + 3) = -20;

	*(net->bias_hidden) = -10;
	*(net->bias_hidden + 1) = 30;

	*(net->weight_hidden_output) = 20;
	*(net->weight_hidden_output + 1) = 20;

	for(int print = 0; print < trainMax; print++)
	{
	//	net->error_rate = 0.0;
		for(int p = 0; p < 4; p++)
		{
			feed_forward(net, p, print);
			//backward_propagation(net, p);
		}
	}
}
