#include "nn.h"
#include "train_tools.h"

#define RED "\033[0;31m"
#define GREEN "\033[0;32m"

int main()
{
    srand(time(NULL));
    neural_net* net = init_net();
    double* matrix = malloc(sizeof(double)*29*29);

    load_weight_bias(net);
    for(size_t i = 0; i < 100000; i++)
    {
        char goal = get_random_matrix(matrix);
        char output = forward(net, matrix, goal);
        backward(net);
        update_biases(net);
        update_weights(net);
        if(i % 100 == 0)
        {
            if(goal == output)
                printf("%s%c --> %c | COST : %f\n", GREEN, goal, output, net->cost);
            else
                printf("%s%c --> %c | COST : %f\n", RED, goal, output, net->cost);
        }            
    }
    save_weight_bias(net);
    return 0;
}