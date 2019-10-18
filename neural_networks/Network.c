//class Network
struct Network{
	//number of neurons in a layer
	double *neurons;
	//number of layers in network
	int *layers;
	//hidden layer weights and biases
	double *weights_hidden;
	double *biases_hidden;
	//output layer weights and biases
	double *weights_output;
	double *biases_output;


}

void InitWeights()
{


}

Network* Initialize_network(Network* self)
{
	Network* result = (Network*) malloc(sizeof(Network));
	Network_init(result, size);
	return result;
}

void Network__reset(Network* self);

void Network__destroy(Network* network) {
  if (network) {
     Network__reset(network);
     free(network);
  }
}


