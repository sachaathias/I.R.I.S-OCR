#include "train_tools.h"

#define LEN 1//103
#define WIDTH 28
#define HEIGHT 28

char files[][13] =
{
    "/a0.txt",
    /*"/a1.txt",
    "/a2.txt",
    "/a3.txt",*/
    "/b0.txt"//,
    /*"/b1.txt",
    "/b2.txt",
    "/b3.txt",
    "/c0.txt",
    "/c1.txt",
    "/c2.txt",
    "/c3.txt",
    "/d0.txt",
    "/d1.txt",
    "/d2.txt",
    "/d3.txt",
    "/e0.txt",
    "/e1.txt",
    "/e2.txt",
    "/e3.txt",
    "/f0.txt",
    "/f1.txt",
    "/f2.txt",
    "/f3.txt",
    "/g0.txt",
    "/g1.txt",
    "/g2.txt",
    "/g3.txt",
    "/h0.txt",
    "/h1.txt",
    "/h2.txt",
    "/h3.txt",
    "/i0.txt",
    "/i1.txt",
    "/i2.txt",
    "/i3.txt",
    "/j0.txt",
    "/j1.txt",
    "/j2.txt",
    "/j3.txt",
    "/k0.txt",
    "/k1.txt",
    "/k2.txt",
    "/k3.txt",
    "/l0.txt",
    "/l1.txt",
    "/l2.txt",
    "/l3.txt",
    "/m0.txt",
    "/m1.txt",
    "/m2.txt",
    "/m3.txt",
    "/n0.txt",
    "/n1.txt",
    "/n2.txt",
    "/n3.txt",
    "/o0.txt",
    "/o1.txt",
    "/o2.txt",
    "/o3.txt",
    "/p0.txt",
    "/p1.txt",
    "/p2.txt",
    "/p3.txt",
    "/q0.txt",
    "/q1.txt",
    "/q2.txt",
    "/q3.txt",
    "/r0.txt",
    "/r1.txt",
    "/r2.txt",
    "/r3.txt",
    "/s0.txt",
    "/s1.txt",
    "/s2.txt",
    "/s3.txt",
    "/t0.txt",
    "/t1.txt",
    "/t2.txt",
    "/t3.txt",
    "/u0.txt",
    "/u1.txt",
    "/u2.txt",
    "/u3.txt",
    "/v0.txt",
    "/v1.txt",
    "/v2.txt",
    "/v3.txt",
    "/w0.txt",
    "/w1.txt",
    "/w2.txt",
    "/w3.txt",
    "/x0.txt",
    "/x1.txt",
    "/x2.txt",
    "/x3.txt",
    "/y0.txt",
    "/y1.txt",
    "/y2.txt",
    "/y3.txt",
    "/z0.txt",
    "/z1.txt",
    "/z2.txt",
    "/z3.txt"*/
};

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

char get_random_matrix(double* matrix)
{
    char* file = files[(int)random(0, LEN)];
    char* f = malloc(sizeof(char)*8);
    sprintf(f, "%c%s", file[1], file);
    file_to_matrix(f, matrix);
    return f[0];
}