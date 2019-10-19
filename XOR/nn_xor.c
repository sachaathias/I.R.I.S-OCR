#include "nn_xor.h"

typedef struct
{
	int nb_input;
	int nb_hidden;

	double *input_value;
	double *hidden_value;
	double output_value;

	double *goal_output;

	double *weight_input_hidden;
	double *weight_hidden_output;

	double error_rate;
} neural_net;

double random()
{
	return (double)rand()/(double)RAND_MAX;
}

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

	return net;
}

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
	}
}

double sigmoid(double x)
{
	return 1/(1+exp(-x));
}

void feed_forward(neural_net *net, int p)
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

	net->error_rate = *(net->goal_output + p) - net->output_value;

	printf("%f XOR %f = %f\n", *(net->input_value + 2 * p),
				*(net->input_value + 2 * p + 1),
				net->output_value);
	printf("Error rate = %f\n", net->error_rate);
}

void XOR()
{
	srand(time(NULL));

	neural_net n = init_net();
	neural_net *net = &n;
	init_value(net);

	for(int p = 0; p < 4; p++)
	{
		feed_forward(net, p);
	}
}
