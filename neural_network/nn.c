#include "nn.h"

double random()
{
    return (double)rand()/(double)RAND_MAX;
}

void print_matrix(int* m)
{
    for(size_t i = 0; i < WIDTH_MATRIX; i++)
    {
        for(size_t j = 0; j < HEIGHT_MATRIX; j++)
        {
            printf("%c", (char)m[j + i * WIDTH_MATRIX]);
        }
        printf("\n");
    }
}

/*int* file_to_matrix(char* f)
{
    FILE* file = NULL;
    file = fopen(f, "r");

    if(file != NULL)
    {
        int* m = malloc(sizeof(int)*WIDTH_MATRIX*HEIGHT_MATRIX);
        for(int i = 0; i < WIDTH_MATRIX; i++)
        {
            for (int j = 0; j < HEIGHT_MATRIX; j++)
            {
                int n = fgetc(file) - 48;
                printf("n = %d\n", n);
                m[j + i * WIDTH_MATRIX] = n;
            }
            fgetc(file);   
        }
        fclose(file);
        print_matrix(m);
        return m;
    }
    else
    {
        errx(1, "File is NULL");
    }
}*/

void file_to_matrix(char* f, int *m)
{
    FILE* file = NULL;
    file = fopen(f, "r");

    if(file != NULL)
    {
        for(int i = 0; i < WIDTH_MATRIX; i++)
        {
            for (int j = 0; j < HEIGHT_MATRIX; j++)
            {
                *(m + (j + i * WIDTH_MATRIX)) = fgetc(file);
            }
            fgetc(file);   
        }
        fclose(file);
        print_matrix(m);
    }
    else
    {
        errx(1, "File is NULL");
    }
}

neural_net init_net()
{
    neural_net net;

    net.nb_input = WIDTH_MATRIX*HEIGHT_MATRIX;
    net.nb_hidden = HIDDEN_N;
    net.nb_output = OUTPUTS;

    net.input_layer = malloc(sizeof(double)*net.nb_input);
    net.hidden_layer = malloc(sizeof(double)*net.nb_hidden);
    net.output_logits = malloc(sizeof(double)*net.nb_output);
    net.output_activation = malloc(sizeof(double)*net.nb_output);

    net.weight_input_hidden = malloc(sizeof(double)*net.nb_input*net.nb_hidden);
    net.weight_hidden_output = malloc(sizeof(double)*net.nb_hidden*net.nb_output);

    net.bias_hidden = malloc(sizeof(double)*net.nb_hidden);
    net.bias_output = malloc(sizeof(double)*net.nb_output);

    net.goal = malloc(sizeof(double)*net.nb_output);

    net.cost_array = malloc(sizeof(double)*net.nb_output);
    net.cost = 0.0;

    net.learning_rate = 0.05;

    return net;
}

void init_value(neural_net *net)
{
    for(size_t i = 0; i < net->nb_input; i++)
    {
        for(size_t h = 0; h < net->nb_hidden; h++)
        {
            net->weight_input_hidden[h + i * net->nb_hidden] = random();
        }
    }

    for (size_t h = 0; h < net->nb_hidden; h++)
    {
        net->bias_hidden[h] = random();
        for(size_t o = 0; o < net->nb_output; o++)
        {
            net->weight_hidden_output[o + h * net->nb_output] = random();
            if(h == 0)
                net->bias_output[o] = random();
        }
    } 
}

void set_input(neural_net* net, int* input)
{
    for(size_t i = 0; i < net->nb_input; i++)
    {
        net->input_layer[i] = (double)input[i];
    }
}

double* goal_array(neural_net *net, char c)
{
    double* goal = calloc(net->nb_output, sizeof(double));

    if(c >= 'A' && c <= 'Z')
        *(goal + (int)c - 65) = 1;
    else if(c >= 'a' && c <= 'z')
        *(goal + (int)c - 97 + 26) = 1;
    return goal;
}

void set_goal(neural_net* net, char c)
{
    double* goal = goal_array(net, c);
    for(size_t o = 0; o < net->nb_output; o++)
    {
        net->goal[o] = (double)goal[o];
    }
}

char get_result(neural_net *net)
{
    double max = 0;
    int posMax = 0;

    //Get Max value
    for(size_t o = 0; o < net->nb_output; o++)
    {
        if(max < net->output_activation[o])
        {
            max = net->output_activation[o];
            posMax = o;
        }
    }

    char c;
    //Upper
    if(posMax <= 25)
        c = posMax + 65;
    //Lower
    else if(posMax > 25 && posMax <= 51)
        c = posMax + 97 - 26;
    return c;
}

void cost(neural_net *net)
{
    double output, goal, cost;
    double total_cost = 0.0
    ;
    for(size_t o = 0; o < net->nb_output; o++)
    {
        output = net->output_activation[o];
        goal = net->goal[o];
        cost = (output - goal) * (output - goal);
        net->cost_array[o] = cost;
        total_cost += cost;
    }
    net->cost = total_cost;
}

void verify(neural_net* net)
{
    double sum_outputs = 0.0;
    for(size_t o = 0; o < net->nb_output; o++)
    {
        sum_outputs += net->output_activation[o];
    }
    printf("Sum results softmax: %f\n", sum_outputs); 
}

void softmax(neural_net* net)
{
    double sum_exp = 0.0;

    for(size_t o = 0; o < net->nb_output; o++)
    {
        sum_exp += exp(net->output_logits[o]);
    }
    for(size_t o = 0; o < net->nb_output; o++)
    {
        net->output_activation[o] = exp(net->output_logits[o]) / sum_exp;
    }
    verify(net);
}

char forward(neural_net* net)
{
    double sum;
    for(size_t h = 0; h < net->nb_input; h++)
    {
        sum =  net->bias_hidden[h];
        for(size_t i = 0; i < net->nb_hidden; i++)
        {
            sum += net->input_layer[i] * net->weight_input_hidden[h + i * net->nb_hidden];
        }
        net->hidden_layer[h] = sum;
    }
    for(size_t o = 0; o < net->nb_output; o++)
    {
        sum = net->bias_output[o];
        for (size_t h = 0; h < net->nb_hidden; h++)
        {
            sum += net->hidden_layer[h] * net->weight_hidden_output[o + h * net->nb_output];
        }
        net->output_logits[o] = sum;
    }
    softmax(net);
    cost(net);

    return get_result(net);
}

void neural_network(neural_net *net, char* file)
{
    char c = file[6];
    int* input = malloc(sizeof(int)*WIDTH_MATRIX*HEIGHT_MATRIX);
    file_to_matrix(file, input);

    set_input(net, input);
    set_goal(net, c);

    char r = forward(net);
    printf("Result: %c | Expected: %c\nCost: %f\n", r, c, net->cost);
}

