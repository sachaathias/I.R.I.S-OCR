#include "xor.h"

double random()
{
    return (double)rand()/(double)RAND_MAX;
    //return (double)rand()/((double)RAND_MAX / 2) - 1;
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

    for(size_t i = 0; i < n->nbI; i++)
    {
        for(size_t h = 0; h < n->nbH; h++)
        {
            n->w_IH[h * n->nbI + i] = random();
        }
    }
    
    /*n->w_IH[0] = random();
    n->w_IH[1] = random();
    n->w_IH[2] = random();
    n->w_IH[3] = random();*/

    for(size_t h = 0; h < n->nbH; h++)
    {
        n->b_H[h] = random();
        n->delta_H[h] = 0.0;
        for(size_t o = 0; o < n->nbO; o++)
        {
            n->w_HO[o * n->nbH + h] = random();
        }
    }

    /*n->w_HO[0] = random();
    n->w_HO[1] = random();
    n->w_HO[2] = random();
    n->w_HO[3] = random();*/

    /*n->b_H[0] = random();
    n->b_H[1] = random();*/

    for(size_t o = 0; o < n->nbO; o++)
    {
        n->b_O[o] = random();
        n->delta_O[o] = 0.0;
    }

    /*n->b_O[0] = random();
    n->b_O[1] = random();*/


    return n;
}

void xor()
{
    int epoch = 1000000;
    srand(time(NULL));

    //INITIALISATION

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

        //FORWARD PROPAGATION   

        for(size_t h = 0; h < net->nbH; h++)
        {
            net->hidden[h] = net->b_H[h];
            for(size_t i = 0; i < net->nbI; i++)
            {
                net->hidden[h] += net->w_IH[h * net->nbI + i] * net->input[i];
            }
            net->hidden[h] = sigmoid(net->hidden[h]);
        }

        //net->hidden[0] = sigmoid(net->w_IH[0] * net->input[0] + net->w_IH[1] * net->input[1] + net->b_H[0]);
        //net->hidden[1] = sigmoid(net->w_IH[2] * net->input[0] + net->w_IH[3] * net->input[1] + net->b_H[1]);

        for(size_t o = 0; o < net->nbO; o++)
        {
            net->output[o] = net->b_O[o];
            for(size_t h = 0; h < net->nbH; h++)
            {
                net->output[o] += net->w_HO[o * net->nbH + h] * net->hidden[h];
            }
            net->output[o] = sigmoid(net->output[o]);
        }

        //net->output[0] = sigmoid(net->w_HO[0] * net->hidden[0] + net->w_HO[1] * net->hidden[1] + net->b_O[0]);
        //net->output[1] = sigmoid(net->w_HO[2] * net->hidden[0] + net->w_HO[3] * net->hidden[1] + net->b_O[1]);

        //BACKWARD PROPAGATION
        
        for(size_t o = 0; o < net->nbO; o++)
        {
            net->delta_O[o] = sigmoid_prime(net->output[o]) * (net->goal[o] - net->output[o]);
        }

        //double delta_output_1 = sigmoid_prime(net->output[0]) * (net->goal[0] - net->output[0]);
        //double delta_output_2 = sigmoid_prime(net->output[1]) * (net->goal[1] - net->output[1]);

        for(size_t h = 0; h < net->nbH; h++)
        {
            net->delta_H[h] = 0.0;
            for(size_t o = 0; o < net->nbO; o++)
            {
                net->delta_H[h] += net->delta_O[o] * net->w_HO[o * net->nbH + h];
            }
            net->delta_H[h] *= sigmoid_prime(net->hidden[h]);
        }

        //double delta_hidden_1 = sigmoid_prime(net->hidden[0]) * (/*delta_output_1*/net->delta_O[0] * net->w_HO[0] + /*delta_output_2*/net->delta_O[1] * net->w_HO[2]);
        //double delta_hidden_2 = sigmoid_prime(net->hidden[1]) * (/*delta_output_1*/net->delta_O[0] * net->w_HO[1] + /*delta_output_2*/net->delta_O[1] * net->w_HO[3]);

        for(size_t o = 0; o < net->nbO; o++)
        {
            net->b_O[o] += net->eta * net->delta_O[o];
            for(size_t h = 0; h < net->nbH; h++)
            {
                net->w_HO[o * net->nbH + h] += net->eta * net->hidden[h] * net->delta_O[o];
            }
        }

        for(size_t h = 0; h < net->nbH; h++)
        {
            net->b_H[h] += net->eta * net->delta_H[h];
            for(size_t i = 0; i < net->nbI; i++)
            {
                net->w_IH[h * net->nbI + i] += net->eta * net->input[i] * net->delta_H[h];
            }
        }

        /*net->b_O[0] += net->eta * net->delta_O[0];//delta_output_1;
        net->b_O[1] += net->eta * net->delta_O[1];//delta_output_2;
        
        net->b_H[0] += net->eta * net->delta_H[0];//delta_hidden_1;
        net->b_H[1] += net->eta * net->delta_H[1];//delta_hidden_2;

        net->w_HO[0] += net->eta * net->hidden[0] * net->delta_O[0];//delta_output_1;
        net->w_HO[1] += net->eta * net->hidden[1] * net->delta_O[0];//delta_output_1;
        net->w_HO[2] += net->eta * net->hidden[0] * net->delta_O[1];//delta_output_2;
        net->w_HO[3] += net->eta * net->hidden[1] * net->delta_O[1];//delta_output_2;

        net->w_IH[0] += net->eta * net->input[0] * net->delta_H[0];//delta_hidden_1;
        net->w_IH[1] += net->eta * net->input[1] * net->delta_H[0];//delta_hidden_1;
        net->w_IH[2] += net->eta * net->input[0] * net->delta_H[1];//delta_hidden_2;
        net->w_IH[3] += net->eta * net->input[1] * net->delta_H[1];//delta_hidden_2;*/


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