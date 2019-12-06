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
                *(m + (j + i * WIDTH)) = (double)fgetc(file);
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
    char* path = malloc(sizeof(char)*25);
    char letter = (char)random_2(0, 51);

    if(letter >= 0 && letter <= 25)
    {
        letter = letter + 65;
        sprintf(path, "train_data/maj/%c/%c%i.txt", letter, letter, (int)random_2(0, 3));
    }
    else
    {
        letter += 97 - 26;
        sprintf(path, "train_data/min/%c/%c%i.txt", letter, letter, (int)random_2(0, 3));
    }
    
    file_to_matrix(path, matrix);
    
    return letter;
}
