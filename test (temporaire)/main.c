#include <stdio.h>
#include <stdlib.h>
#include <err.h>
#include "load_and_binarise.h"

int main(int argc, char** argv)
{
	if(argc != 2)
		errx(1, "No file specified");
	char* file = argv[1];
	save_BMP(file);
	return 0;
}
