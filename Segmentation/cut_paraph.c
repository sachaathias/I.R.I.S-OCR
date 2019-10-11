#include <stdio.h>
#include "cut_paraph.h"

//Return 1 if the line at the index i is blank else return0
int detect_blank_line(image[][], size_t i)
{
	

// Detect the begining and the end of each paragraph
void detect_paraph(image[][], size_t i, size_t j)
{
	for(int index_i = 0; index_i < i; index_i++)
	{
		// Check if this line is blank
		for(int index_j = 0; index_j < j; index_j++)
		{

