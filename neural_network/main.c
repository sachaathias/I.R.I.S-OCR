#include "nn.h"
#include "train_tools.h"

int main()
{
    srand(time(NULL));
    neural_net* net = init_net();
    double* matrix = malloc(sizeof(double)*29*29);

    load_weight_bias(net);
    for(size_t i = 0; i < 10000; i++)
    {
        char goal = get_random_matrix(matrix);
        char output = forward(net, matrix, goal);
        backward(net);
        update_biases(net);
        update_weights(net);
        if(i % 100 == 0)
        {
            printf("%c --> %c | COST : %f\n", goal, output, net->cost);
        }            
    }
    save_weight_bias(net);
    return 0;
}