#include "nn.h"

int main(int argc, char** argv)
{
    srand(time(NULL));
    if(argc != 2)
        errx(1, "No file specified");
    neural_net n = init_net();
    neural_net *net = &n;
    init_value(net);

    neural_network(net, argv[1]);
}