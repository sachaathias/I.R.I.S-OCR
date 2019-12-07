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
        
        printf("---LOAD---\n");
        char str[MAX_SIZE_LINE] = "";
        //WEIGHT_INPUT_HIDDEN
        for(size_t i = 0; i < net->nb_input; i++)
        {
            for(size_t h = 0; h < net->nb_hidden; h++)
            {
                //fgets(str, MAX_SIZE_LINE, file);
                //net->w_IH[i][h] = atof(str);
		fscanf(file, "%lf\n", &net->w_IH[i][h]);
            }
        }

        //WEIGHT_HIDDEN_OUTPUT
        for(size_t h = 0; h < net->nb_hidden; h++)
        {
            for(size_t o = 0; o < net->nb_output; o++)
            {
                //fgets(str, MAX_SIZE_LINE, file);
                //net->w_HO[h][o] = atof(str);
		fscanf(file, "%lf\n", &net->w_HO[h][o]);
            }
        }

        //BIAS_HIDDEN
        for(size_t h = 0; h < net->nb_hidden; h++)
        {
            //fgets(str, MAX_SIZE_LINE, file);
            //net->b_H[h] = atof(str);
	    fscanf(file, "%lf\n", &net->b_H[h]);
        }

        //BIAS_OUTPUT
        for(size_t o = 0; o < net->nb_output; o++)
        {
            //fgets(str, MAX_SIZE_LINE, file);
            //net->b_O[o] = atof(str);
	    fscanf(file, "%lf\n", &net->b_O[o]);
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
        printf("---SAVE---\n");
        //WEIGHT_INPUT_HIDDEN
        for(size_t i = 0; i < net->nb_input; i++)
        {
            for(size_t h = 0; h < net->nb_hidden; h++)
            {
                fprintf(file, "%lf\n", net->w_IH[i][h]);
            }
        }

        //WEIGHT_HIDDEN_OUTPUT
        for(size_t h = 0; h < net->nb_hidden; h++)
        {
            for(size_t o = 0; o < net->nb_output; o++)
            {
                fprintf(file, "%lf\n", net->w_HO[h][o]);
            }
        }

        //BIAS_HIDDEN
        for(size_t h = 0; h < net->nb_hidden; h++)
        {
            fprintf(file, "%lf\n", net->b_H[h]);
        }

        //BIAS_OUTPUT
        for(size_t o = 0; o < net->nb_output; o++)
        {
            fprintf(file, "%lf\n", net->b_O[o]);
	}

        fclose(file);
    }
    else
    {
        errx(1, "File is NULL");
    }
}
