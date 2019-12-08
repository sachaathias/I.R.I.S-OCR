#include "train_tools.h"

#define WIDTH 28
#define HEIGHT 28

double random_2(int min, int max)
{
	return (double)(rand() % (max - min + 1) + min);
}

void file_to_matrix(char* f, double *m)
{
    FILE* file = NULL;
    file = fopen(f, "r");

    if(file != NULL)
    {
        for(int i = 0; i < HEIGHT; i++)
        {
            for (int j = 0; j < WIDTH; j++)
            {
                m[i + j * WIDTH] = (double)fgetc(file)-48;
            }
            fgetc(file);
        }
        fclose(file);
    }
    else
    {
        errx(1, "File is NULL");
    }
}

//train_data/[min-maj]/[$letter]/[$letter][0-3].txt
char get_random_matrix(double* matrix)
{
    char* path = malloc(sizeof(char)*38);
    char letter = (char)random_2(26, 51);

    if(letter >= 0 && letter <= 25)
    {
        letter = letter + 65;
        sprintf(path, "neural_network/train_data/maj/%c/%c%i.txt", letter, letter, (int)random_2(0, 7));
    }
    else
    {
        letter += 97 - 26;
        sprintf(path, "neural_network/train_data/min/%c/%c.txt", letter, letter);
    }
    
    file_to_matrix(path, matrix);
    
    return letter;
}
