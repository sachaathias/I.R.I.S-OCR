#ifndef MATRIX_H
#define MATRIX_H

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct matrix{
	int rows;
	int cols;
	double *data;
}matrix;
struct matrix * newMatrix(int rows, int cols);
int deleteMatrix(struct matrix * mtx);

#define ELEM(mtx, row, col) \
  mtx->data[(col-1) * mtx->rows + (row-1)]

struct matrix * copyMatrix(struct matrix * mtx);
struct matrix * squareMatrix(struct matrix * m, int n);
int setElement(struct matrix * mtx, int row, int col, double val);
int getElement(struct matrix * mtx, int row, int col, double * val);
int nRows(struct matrix * mtx, int * n);
int nCols(struct matrix * mtx, int * n);
int printMatrix(struct matrix * mtx);
int transpose(struct matrix * in, struct matrix * out);
int sum(struct matrix * mtx1,struct  matrix * mtx2, struct matrix * sum);
int product(struct matrix * mtx1, struct matrix * mtx2, struct matrix * prod);
int dotProduct(struct matrix * v1, struct matrix * v2, double * prod);
int identity(struct matrix * m);
int isSquare(struct matrix * mtx);
int isDiagonal(struct matrix * mtx);
int isUpperTriangular(struct matrix * mtx);
int diagonal(struct matrix * v, struct matrix * mtx);
struct matrix * scale_up(struct matrix * m, int rows, int cols);
struct matrix * scale_down(struct matrix * m, int rows, int cols);

#endif
