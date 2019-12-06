#include "xor.h"

static inline double random()
{
    return (double)rand()/(double)RAND_MAX;
    //return (double)rand()/((double)RAND_MAX / 2) - 1;
}

static inline double sigmoid(double x)
{
    return 1.0/(1.0+exp(-x));
}

static inline double sigmoid_prime(double x)
{
    return x*(1-x);
}

double cost_xor(nn* net)
{
    double cost = 0.0;

    for(size_t o = 0; o < net->nbO; o++)
    {
        cost += pow(net->goal[o] - net->output[o], 2);
    }
    return 0.5 * cost;
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

    for(size_t h = 0; h < n->nbH; h++)
    {
        n->b_H[h] = random();
        n->delta_H[h] = 0.0;
        for(size_t o = 0; o < n->nbO; o++)
        {
            n->w_HO[o * n->nbH + h] = random();
        }
    }

    for(size_t o = 0; o < n->nbO; o++)
    {
        n->b_O[o] = random();
        n->delta_O[o] = 0.0;
    }

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

        for(size_t o = 0; o < net->nbO; o++)
        {
            net->output[o] = net->b_O[o];
            for(size_t h = 0; h < net->nbH; h++)
            {
                net->output[o] += net->w_HO[o * net->nbH + h] * net->hidden[h];
            }
            net->output[o] = sigmoid(net->output[o]);
        }

	//BACKWARD PROPAGATION

        for(size_t o = 0; o < net->nbO; o++)
        {
            net->delta_O[o] = sigmoid_prime(net->output[o]) * (net->goal[o] - net->output[o]);
        }

        for(size_t h = 0; h < net->nbH; h++)
        {
            net->delta_H[h] = 0.0;
            for(size_t o = 0; o < net->nbO; o++)
            {
                net->delta_H[h] += net->delta_O[o] * net->w_HO[o * net->nbH + h];
            }
            net->delta_H[h] *= sigmoid_prime(net->hidden[h]);
        }

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

        if(i >= epoch - 4)
        {
            int result;
            if(net->output[0] > net->output[1])
                result = 0;
            else
                result = 1;

            printf("(%lf, %lf):\n", net->input[0], net->input[1]);
            printf("0: %lf\n1: %lf\n", net->output[0], net->output[1]);

            if(result == expected)
                printf("%s", GREEN);
            else
                printf("%s", RED);
            printf("--> %i\n", result);
            printf("%s", DEFAULT);
            printf("COST : %lf\n\n", cost_xor(net));
        }
    }
}
