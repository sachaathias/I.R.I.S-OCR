#include <stdio.h>
#include <stdlib.h>
#include <err.h>
#include "Tests/tests_functions.h"

int main(int argc, char** argv)
{
	if(argc != 2)
		errx(1, "No file specified");
	char* file = argv[1];
	save_BMP_test(file);
	return 0;
}
