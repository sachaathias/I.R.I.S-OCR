#include <stdio.h>
#include <stdlib.h>
#include <err.h>
#include <string.h>
#include "Tests/tests_functions.h"
#include "XOR/nn_xor.h"

int main(int argc, char** argv)
{
/*	if(argc != 2)
		errx(1, "No file specified");
	char* file = argv[1];
	display_image_test(file);
	XOR();
	return 0;
*/
	char* error = " * Use \'-xor\' to run XOR neural network\n * Use \'-img_trt <image_path>\' to run\n\tbinarisation and segmentation";
	if(argc < 2)
	{
		printf("Not enough arguments\n%s\n", error);
		return 1;
	}
	else
	{
		for(int i = 1; i < argc; i++)
		{
			char* arg = argv[i];
			if(strcmp(arg, "-xor") == 0)
			{
				XOR();
			}
			else if(strcmp(arg, "-img_trt") == 0)
			{
				if(i+1 > argc)
					printf("No file specified\n%s\n", error);
				else
				{
					char* file = argv[i+1];
					i++;
					display_image_test(file);
				}
			}
			else
			{
				printf("Unknown argument \"%s\"\n%s\n", arg, error);
			}
		}
		return 0;
	}
}
