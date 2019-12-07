#include <stdio.h>
#include <stdlib.h>
#include <err.h>
#include <string.h>
#include "Tests/tests_functions.h"
#include "XOR/xor.h"
#include "neural_network/main_nn.h"
#include "interface_graphique/interface.h"


void help()
{
    printf("##################################################################\n");
    printf("#    Welcome to I.R.I.S's OCR V2                                 #\n\
#              Here is some commands :                           #\n");
    printf("#       %s--help%s  To picture commands                              #\n",GREEN,DEFAULT);
    printf("#       %s--XOR%s  To show the neural network for the XOR function   # \n",GREEN,DEFAULT);
    printf("#       %s--Train%s To Train the neural network                      #\n",GREEN,DEFAULT);
    printf("#       %s--img_trt <image_path>%s To run                            #\n\
#              binarisation and segmentation                     #\n",GREEN,DEFAULT);
    printf("#       %s--start%s  Launch GUI                                      #\n",GREEN,DEFAULT);
    printf("##################################################################\n");
}


int main(int argc, char** argv)
{
    if(argc < 2)
    {
        printf("Not enough arguments:\n\
                \tuse --help to show each commands\n");
        return 0;
    }
     else
    {
        for(int i = 1; i < argc; i++)
        {
            char* arg = argv[i];
            if (strcmp(arg,"--help")==0)
            {
                help();
            }
            else if (strcmp(arg,"--start")==0)
            {
                UI(argc, argv);
            }
            else if(strcmp(arg, "--XOR") == 0)
            {
                xor();
            }
            else if(strcmp(arg, "--Train")==0)
            {
                train();
            }
            else if(strcmp(arg, "--img_trt") == 0)
            {
                if(i+1 > argc)
                    printf("No file specified\n");
                else
                {
                    char* file = argv[i+1];
                    i++;
                    display_image_test(file);
                }
            }
            else
            {
                printf("Unknown argument \"%s\" use --help to show commands\n", arg);
            }
        }
        return 0;
    }

}
