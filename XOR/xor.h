#ifndef XOR_H
#define XOR_H

#include <math.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>

#define RED "\033[0;31m"
#define GREEN "\033[0;32m"
#define DEFAULT "\033[0;0m"

typedef struct
{
    size_t nbI;
    size_t nbH;
    size_t nbO;

    double input[2];
    double hidden[2];
    double output[2];
    double goal[2];

    double w_IH[4];
    double w_HO[4];

    double b_H[2];
    double b_O[2];

    double delta_O[2];
    double delta_H[2];

    double eta;
}nn;

void xor();

#endif
