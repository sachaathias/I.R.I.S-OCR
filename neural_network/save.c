#include "save.h"

void load_weight_bias(neural_net* net)
{
    /*
    WEIGHT_INPUT_HIDDEN
    WEIGHT_HIDDEN_OUTPUT
    BIAS_HIDDEN
    BIAS_OUTPUT
    */
    FILE* file = NULL;
    file = fopen("netvalue.nn", "r");

    if(file != NULL)
    {
        char str[MAX_SIZE_LINE] = "";
        //WEIGHT_INPUT_HIDDEN
        for(size_t i = 0; i < net->nb_input; i++)
        {
            for(size_t h = 0; h < net->nb_hidden; h++)
            {
                fgets(str, MAX_SIZE_LINE, file);
                net->w_IH[h * net->nb_input + i] = atof(str);
            }
        }

        //WEIGHT_HIDDEN_OUTPUT
        for(size_t h = 0; h < net->nb_hidden; h++)
        {
            for(size_t o = 0; o < net->nb_output; o++)
            {
                fgets(str, MAX_SIZE_LINE, file);
                net->w_HO[o * net->nb_hidden + h] = atof(str);
            }
        }

        //BIAS_HIDDEN
        for(size_t h = 0; h < net->nb_hidden; h++)
        {
            fgets(str, MAX_SIZE_LINE, file);
            net->b_H[h] = atof(str);
        }

        //BIAS_OUTPUT
        for(size_t o = 0; o < net->nb_output; o++)
        {
            fgets(str, MAX_SIZE_LINE, file);
            net->b_O[o] = atof(str);
        }

        fclose(file);
    }
}

void save_weight_bias(neural_net* net)
{
    /*
    WEIGHT_INPUT_HIDDEN
    WEIGHT_HIDDEN_OUTPUT
    BIAS_HIDDEN
    BIAS_OUTPUT
    */
    FILE* file = NULL;
    file = fopen("netvalue.nn", "w");

    if(file != NULL)
    {
        //WEIGHT_INPUT_HIDDEN
        for(size_t i = 0; i < net->nb_input; i++)
        {
            for(size_t h = 0; h < net->nb_hidden; h++)
            {
                fprintf(file, "%f\n", net->w_IH[h * net->nb_input + i]);
            }
        }

        //WEIGHT_HIDDEN_OUTPUT
        for(size_t h = 0; h < net->nb_hidden; h++)
        {
            for(size_t o = 0; o < net->nb_output; o++)
            {
                fprintf(file, "%f\n", net->w_HO[o * net->nb_hidden + h]);
            }
        }

        //BIAS_HIDDEN
        for(size_t h = 0; h < net->nb_hidden; h++)
        {
            fprintf(file, "%f\n", net->b_H[h]);
        }

        //BIAS_OUTPUT
        for(size_t o = 0; o < net->nb_output; o++)
        {
            fprintf(file, "%f", net->b_O[o]);
            if(o < net->nb_output - 1)
                fprintf(file, "\n");
        }

        fclose(file);
    }
    else
    {
        errx(1, "File is NULL");
    }
}