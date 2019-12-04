#include "nn.h"
#include "save.h"
#include "train_tools.h"
#include <time.h>

#define RED "\033[0;31m"
#define GREEN "\033[0;32m"

int main()
{
    srand(time(NULL));
    neural_net *net = init_net();

    double *matrix = malloc(sizeof(double)*28*28);

    load_weight_bias(net);
    for(size_t epoch = 0; epoch < 1000000; epoch++)
    {
        char goal = get_random_matrix(matrix);
        char output = forward(net, matrix, goal);

        if(goal == output)
                printf("%s%c --> %c | COST : %f\n", GREEN, goal, output, net->cost);
        else
            printf("%s%c --> %c | COST : %f\n", RED, goal, output, net->cost);

        backward(net);
        update_weights(net);
        update_bias(net);
    }

    save_weight_bias(net);
    return 0;
}