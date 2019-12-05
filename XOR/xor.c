#include "xor.h"

double random()
{
    return (double)rand()/(double)RAND_MAX;
    //return (double)rand()/((double)RAND_MAX / 2) - 1;
}

double random_2()
{
    double r = (double)rand()/(double)RAND_MAX;
    if(r > 0.5)
        return 1.0;
    return 0.0;
}

double sigmoid(double x)
{
    return 1.0/(1.0+exp(-x));
}

double sigmoid_prime(double x)
{
    return x*(1-x);
}

double cost(nn* net)
{
    return 0.5 * ((net->goal[0] - net->output[0]) * (net->goal[0] - net->output[0]) + (net->goal[1] - net->output[1]) * (net->goal[1] - net->output[1]));
}

nn* init()
{
    nn *n = malloc(sizeof(nn));
    
    n->nbI = 2;
    n->nbH = 2;
    n->nbO = 2;

    n->eta = 0.5;

    n->w_IH[0] = random();
    n->w_IH[1] = random();
    n->w_IH[2] = random();
    n->w_IH[3] = random();

    n->w_HO[0] = random();
    n->w_HO[1] = random();
    n->w_HO[2] = random();
    n->w_HO[3] = random();

    n->b_H[0] = random();
    n->b_H[1] = random();

    n->b_O[0] = random();
    n->b_O[1] = random();

    return n;
}

void xor()
{
    int epoch = 10000;
    srand(time(NULL));
    nn* net = init();
    int expected;
    for(int i = 0; i < epoch; i++)
    {
        switch (i % 4)
        {
        case 0:
            net->input[0] = 0;
            net->input[1] = 1;
            net->goal[0] = 0;
            net->goal[1] = 1;
            expected = 1;
            break;
        case 1:
            net->input[0] = 1;
            net->input[1] = 0;
            net->goal[0] = 0;
            net->goal[1] = 1;
            expected = 1;
            break;
        case 2:
            net->input[0] = 0;
            net->input[1] = 0;
            net->goal[0] = 1;
            net->goal[1] = 0;
            expected = 0;
            break;
        case 3:
            net->input[0] = 1;
            net->input[1] = 1;
            net->goal[0] = 1;
            net->goal[1] = 0;
            expected = 0;
            break;
        
        default:
            break;
        }        

        net->hidden[0] = sigmoid(net->w_IH[0] * net->input[0] + net->w_IH[1] * net->input[1] + net->b_H[0]);
        net->hidden[1] = sigmoid(net->w_IH[2] * net->input[0] + net->w_IH[3] * net->input[1] + net->b_H[1]);

        net->output[0] = sigmoid(net->w_HO[0] * net->hidden[0] + net->w_HO[1] * net->hidden[1] + net->b_O[0]);
        net->output[1] = sigmoid(net->w_HO[2] * net->hidden[0] + net->w_HO[3] * net->hidden[1] + net->b_O[1]);

        double delta_output_1 = sigmoid_prime(net->output[0]) * (net->goal[0] - net->output[0]);
        double delta_output_2 = sigmoid_prime(net->output[1]) * (net->goal[1] - net->output[1]);

        double delta_hidden_1 = sigmoid_prime(net->hidden[0]) * (delta_output_1 * net->w_HO[0] + delta_output_2 * net->w_HO[2]);
        double delta_hidden_2 = sigmoid_prime(net->hidden[1]) * (delta_output_1 * net->w_HO[1] + delta_output_2 * net->w_HO[3]);

        net->b_O[0] += net->eta * delta_output_1;
        net->b_O[1] += net->eta * delta_output_2;
        
        net->b_H[0] += net->eta * delta_hidden_1;
        net->b_H[1] += net->eta * delta_hidden_2;

        net->w_HO[0] += net->eta * net->hidden[0] * delta_output_1;
        net->w_HO[1] += net->eta * net->hidden[1] * delta_output_1;
        net->w_HO[2] += net->eta * net->hidden[0] * delta_output_2;
        net->w_HO[3] += net->eta * net->hidden[1] * delta_output_2;

        net->w_IH[0] += net->eta * net->input[0] * delta_hidden_1;
        net->w_IH[1] += net->eta * net->input[1] * delta_hidden_1;
        net->w_IH[2] += net->eta * net->input[0] * delta_hidden_2;
        net->w_IH[3] += net->eta * net->input[1] * delta_hidden_2;


        if(i >= epoch - 4)
        {
            int result;
            if(net->output[0] > net->output[1])
                result = 0;
            else
                result = 1;
            if(result == expected)
                printf("%s", GREEN);
            else
                printf("%s", RED);

            printf("(%lf, %lf):\n", net->input[0], net->input[1]);
            printf("0: %lf\n1: %lf\n", net->output[0], net->output[1]);

            printf("--> %i\n", result);
            printf("COST : %lf\n\n", cost(net));
        }
    }
}