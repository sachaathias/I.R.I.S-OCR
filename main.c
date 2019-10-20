#include <stdio.h>
#include <stdlib.h>
#include <err.h>
#include "Tests/tests_functions.h"
#include "XOR/nn_xor.h"

int main(int argc, char** argv)
{
	if(argc != 2)
		errx(1, "No file specified");
	char* file = argv[1];
	display_image_test(file);
	XOR();
	return 0;
}
