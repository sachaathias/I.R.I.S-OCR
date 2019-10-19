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

	//Use for error_rate and learning
	double *goal_output;

	//Weight of each transitions between two layers
	double *weight_input_hidden;
	double *weight_hidden_output;

	double error_rate;

	//Delta of each weight for learning
	double *delta_weight_input_hidden;
	double *delta_weight_hidden_output;

	//Delta of each value in each layer
	double delta_output_value;
	double *delta_hidden_value;

	double learning_rate;
	double alpha;
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

	net.goal_output = malloc(sizeof(double) * 4);

	net.weight_input_hidden = malloc(sizeof(double) * net.nb_input * net.nb_hidden);
	net.weight_hidden_output = malloc(sizeof(double) * net.nb_hidden);

	net.error_rate = 0.0;

	net.delta_weight_input_hidden = malloc(sizeof(double) * net.nb_input * net.nb_hidden);
	net.delta_weight_hidden_output = malloc(sizeof(double) * net.nb_hidden);

	net.delta_output_value = 0.0;
	net.delta_hidden_value = malloc(sizeof(double) * net.nb_hidden);

	net.learning_rate = 0.5;
	net.alpha = 0.9;

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
			*(net->delta_weight_input_hidden + (h + i * net->nb_hidden)) = 0.0;
		}
	}

	for(int h = 0; h < net->nb_hidden; h++)
	{
		*(net->weight_hidden_output + h) = random();
		*(net->delta_weight_hidden_output + h) = 0.0;
	}
}

//Return the Sigmoid of a number
double sigmoid(double x)
{
	return 1/(1+exp(-x));
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
		*(net->hidden_value + i) = sigmoid(sum_hidden);
	}

	double sum_output = 0.0;
	for(int h = 0; h < net->nb_hidden; h++)
	{
		sum_output += *(net->hidden_value + h) * *(net->weight_hidden_output + h);
	}
	net->output_value = sigmoid(sum_output);

	net->error_rate = 0.5 * (*(net->goal_output + p)
		- net->output_value) * (*(net->goal_output + p)
		- net->output_value);

	if(print % 100 == 0)
	{
		printf("%f XOR %f = %f\n", *(net->input_value + 2 * p),
					*(net->input_value + 2 * p + 1),
					net->output_value);
		printf("\tError rate = %f\n\n", net->error_rate);
	}
}

//Backward propagation (learning) for neural net
void backward_propagation()
{
	//FIXME
}

//Main function of XOR neural net
void XOR()
{
	srand(time(NULL));
	
	int trainMax = 10000;
	neural_net n = init_net();
	neural_net *net = &n;
	init_value(net);

	for(int print = 0; print < trainMax; print++)
	{
		for(int p = 0; p < 4; p++)
		{
			feed_forward(net, p, print);
		}
	}
}
