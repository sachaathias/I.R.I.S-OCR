#include "train_tools.h"

#define LEN 103
#define WIDTH 29
#define HEIGHT 29

char files[][13] =
{
    "Train/a0.txt",
    "Train/a1.txt",
    "Train/a2.txt",
    "Train/a3.txt",
    "Train/b0.txt",
    "Train/b1.txt",
    "Train/b2.txt",
    "Train/b3.txt",
    "Train/c0.txt",
    "Train/c1.txt",
    "Train/c2.txt",
    "Train/c3.txt",
    "Train/d0.txt",
    "Train/d1.txt",
    "Train/d2.txt",
    "Train/d3.txt",
    "Train/e0.txt",
    "Train/e1.txt",
    "Train/e2.txt",
    "Train/e3.txt",
    "Train/f0.txt",
    "Train/f1.txt",
    "Train/f2.txt",
    "Train/f3.txt",
    "Train/g0.txt",
    "Train/g1.txt",
    "Train/g2.txt",
    "Train/g3.txt",
    "Train/h0.txt",
    "Train/h1.txt",
    "Train/h2.txt",
    "Train/h3.txt",
    "Train/i0.txt",
    "Train/i1.txt",
    "Train/i2.txt",
    "Train/i3.txt",
    "Train/j0.txt",
    "Train/j1.txt",
    "Train/j2.txt",
    "Train/j3.txt",
    "Train/k0.txt",
    "Train/k1.txt",
    "Train/k2.txt",
    "Train/k3.txt",
    "Train/l0.txt",
    "Train/l1.txt",
    "Train/l2.txt",
    "Train/l3.txt",
    "Train/m0.txt",
    "Train/m1.txt",
    "Train/m2.txt",
    "Train/m3.txt",
    "Train/n0.txt",
    "Train/n1.txt",
    "Train/n2.txt",
    "Train/n3.txt",
    "Train/o0.txt",
    "Train/o1.txt",
    "Train/o2.txt",
    "Train/o3.txt",
    "Train/p0.txt",
    "Train/p1.txt",
    "Train/p2.txt",
    "Train/p3.txt",
    "Train/q0.txt",
    "Train/q1.txt",
    "Train/q2.txt",
    "Train/q3.txt",
    "Train/r0.txt",
    "Train/r1.txt",
    "Train/r2.txt",
    "Train/r3.txt",
    "Train/s0.txt",
    "Train/s1.txt",
    "Train/s2.txt",
    "Train/s3.txt",
    "Train/t0.txt",
    "Train/t1.txt",
    "Train/t2.txt",
    "Train/t3.txt",
    "Train/u0.txt",
    "Train/u1.txt",
    "Train/u2.txt",
    "Train/u3.txt",
    "Train/v0.txt",
    "Train/v1.txt",
    "Train/v2.txt",
    "Train/v3.txt",
    "Train/w0.txt",
    "Train/w1.txt",
    "Train/w2.txt",
    "Train/w3.txt",
    "Train/x0.txt",
    "Train/x1.txt",
    "Train/x2.txt",
    "Train/x3.txt",
    "Train/y0.txt",
    "Train/y1.txt",
    "Train/y2.txt",
    "Train/y3.txt",
    "Train/z0.txt",
    "Train/z1.txt",
    "Train/z2.txt",
    "Train/z3.txt"
};

void file_to_matrix(char* f, double *m)
{
    FILE* file = NULL;
    file = fopen(f, "r");

    if(file != NULL)
    {
        for(int i = 0; i < 29; i++)
        {
            for (int j = 0; j < 29; j++)
            {
                *(m + (j + i * 29)) = (double)fgetc(file);
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

char get_random_matrix(double* matrix)
{
    char* file = files[(int)random(0, LEN)];
    file_to_matrix(file, matrix);
    return file[6];
}

char get_matrix(double* matrix, size_t i)
{
    char* file = files[i%LEN];
    file_to_matrix(file, matrix);
    return file[6];
}