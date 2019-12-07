#include "main_nn.h"

void train()
{
    srand(time(NULL));
    neural_net *net = init_net();

    double *matrix = malloc(sizeof(double)*28*28);

    load_weight_bias(net);
    for(size_t epoch = 0; epoch < 1000000; epoch++)
    {
        char goal = get_random_matrix(matrix);
        char output = forward(net, matrix, goal);

        if(epoch % 1000 == 0)
        {
            if(goal == output)
                printf("%s%zu | %c --> %c | COST : %f%s\n", GREEN, epoch, goal, output, net->cost, DEFAULT);
            else
                printf("%s%zu | %c --> %c | COST : %f%s\n", RED, epoch, goal, output, net->cost, DEFAULT);
            printf("%s", DEFAULT);
            //save_weight_bias(net);
        }

        backward(net);
        update_weights_bias(net);
    }
    save_weight_bias(net);
}

neural_net *init_net_train()
{
	srand(time(NULL));
	neural_net *net = init_net();

	load_weight_bias(net);

	return net;
}
