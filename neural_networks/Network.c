//class Network
struct Network{
	uint layers;
	float weights[5];
	float bias[2];
	int size;


}

void Network_init(Network* self, int size)
{
	
}

Network* Network_create(Network* self, int size)
{
	Network* result = (Network*) malloc(sizeof(Network));
	Network_init(result, size);
	return result;
}

void Network_reset(Network* self);

void Point__destroy(Network* point) {
  if (point) {
     Point__reset(point);
     free(point);
  }
}


