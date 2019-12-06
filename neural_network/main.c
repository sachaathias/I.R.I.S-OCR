#include "nn.h"
#include "save.h"
#include "train_tools.h"
#include <time.h>

#define RED "\033[0;31m"
#define GREEN "\033[0;32m"
#define DEFAULT "\033[0;0m"

int main()
{
    srand(time(NULL));
    neural_net *net = init_net();

    double *matrix = malloc(sizeof(double)*28*28);

    load_weight_bias(net);
    for(size_t epoch = 0; epoch < 10000000000; epoch++)
    {
        char goal = get_random_matrix(matrix);
        char output = forward(net, matrix, goal);

        if(epoch % 10000 == 0)
        {
            if(goal == output)
            printf("%s%c --> %c | COST : %f\n", GREEN, goal, output, net->cost);
            else
                printf("%s%c --> %c | COST : %f\n", RED, goal, output, net->cost);
            printf("%s", DEFAULT);
        }   

        backward(net);

        if(epoch % 100 == 0)
        {
            update_weights_bias(net);
            reset_deltas(net);
        }
        if(epoch % 100000 == 0)
            save_weight_bias(net);
           
    }
    save_weight_bias(net);

    return 0;
}