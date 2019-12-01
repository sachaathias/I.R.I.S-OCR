#include "matrix.h"

/* Creates a ``rows by cols'' matrix with all values 0.  
 * Returns NULL if rows <= 0 or cols <= 0 and otherwise a
 * pointer to the new matrix.
 */
struct matrix *newMatrix(int rows, int cols) {
  if (rows <= 0 || cols <= 0) return NULL;

  // allocate a matrix structure
  struct matrix *m;
  m = (struct matrix*)malloc(sizeof(struct matrix));

  // set dimensions
  m->rows = rows;
  m->cols = cols;

  // allocate a double array of length rows * cols
  m->data = (double*)malloc(rows*cols*sizeof(double));
  // set all data to 0
  int i;
  for (i = 0; i < rows*cols; i++)
    m->data[i] = 0.0;

  return m;
}

struct matrix * scale_up(struct matrix * m, int rows, int cols)
{
  struct matrix *scaled = newMatrix(rows, cols);

  int factor_h = rows / m->rows;
  int factor_w = cols / m->cols;

  int start_h = (rows % m ->rows) / 2;
  int start_w = (cols % m ->cols) / 2;
  
  for (int i = 0; i < h; i++)
  {
    for (int j = 0; j < w; j++)
    {
      double value = ELEM(m, i,  j);

      if (value > 0)
      {
        int k = start_h + i * factor_h;
        for (; k < start_h + (i + 1) * factor_h; k++)
        {
          int l = start_w + j * factor_w;
          for (; l < start_w + (j + 1) * factor_w; l++)
          {
            setElement(scaled, k, l, (double)1);
          }
        }
      }
      
    }
  }
}
/*
struct matrix * scale_down(struct matrix * m, int rows, int cols)
{
  struct matrix *scaled = newMatrix(rows, cols);
  int *scaled_tmp = calloc(rows*cols, sizeof(int));

  int factor_h = rows / m->rows;
  int factor_w = cols / m->cols;

  int start_h = (rows % m ->rows) / 2;
  int start_w = (cols % m ->cols) / 2;

  int count = 0;
  int sum = 0;
  
  for (int i = 0; i < h; i++)
  {
    for (int j = 0; j < w; j++)
    {
      int sum_curr = 0;

      int k = start_h + i * factor_h;
      for (; k < start_h + (i + 1) * factor_h; k++)
      {
        int l = start_w + j * factor_w;
        for (; l < start_w + (j + 1) * factor_w; l++)
        {
          double value = ELEM(m, i,  j);

          if (value > 0)
            sum_curr++;
        }
      }
      
      if (sum_curr > 0)
      {
        sum += sum_curr;
        count ++;

        scaled_tmp[i * rows + j] = sum_curr;
      }
    }
  }

  int average = sum / count;

  for (int i = 0; i < rows*cols; i++)
    if (scaled_tmp[i] >= average)
      setElement(scaled, , j_s, 
}*/
// This function transform a matrix to a square matrix of dimension n 
struct matrix * squareMatrix(struct matrix * m, int n)
{
	// Test if we can fill the square matrix of length n
	if(m->rows > n || m ->cols > n)
	{
		printf("ERROR");
		return 0;
	}
	else
	{
		struct matrix *square = newMatrix(n, n);
		int square_center = n / 2;

		int h = m->rows;
		int w = m->cols;

		// Fill square with 0
		for(int i = 0; i < n; i++)
		{
			for(int j = 0; j < n; j++)
			{
				setElement(square, i, j, (double)0);
			}
		}

		// Find the point where we can copy m in square
		int x = square_center - h/2;
		int y = square_center - w/2;

		// Copy m in square on the center
		for(int i_s = x, i_m = 0; i_s < n ||  i_m < h ; i_s++, i_m++)
		{
			for(int j_s = y,  j_m = 0; j_s < n || j_m < w; j_s++, j_m++)
			{
				setElement(square, i_s, j_s, ELEM(m, i_m,  j_m));
			}
		}

		return square;
	}
}



/* Deletes a matrix.  Returns 0 if successful and -1 if mtx 
 * is NULL.
 */
int deleteMatrix(struct matrix * mtx) {
  if (!mtx) return -1;
  // free mtx's data
  assert (mtx->data);
  free(mtx->data);
  // free mtx itself
  free(mtx);
  return 0;
}

#define ELEM(mtx, row, col) \
  mtx->data[(col-1) * mtx->rows + (row-1)]

/* Copies a matrix.  Returns NULL if mtx is NULL.
 */
struct matrix * copyMatrix(struct matrix * mtx) {
  if (!mtx) return NULL;

  // create a new matrix to hold the copy
  struct matrix * cp = newMatrix(mtx->rows, mtx->cols);

  // copy mtx's data to cp's data
  memcpy(cp->data, mtx->data, 
         mtx->rows * mtx->cols * sizeof(double));

  return cp;
}

/* Sets the (row, col) element of mtx to val.  Returns 0 if
 * successful, -1 if mtx is NULL, and -2 if row or col are
 * outside of the dimensions of mtx.
 */
int setElement(struct matrix * mtx, int row, int col, double val)
{
  if (!mtx) return -1;
  assert (mtx->data);
  if (row <= 0 || row > mtx->rows ||
      col <= 0 || col > mtx->cols)
    return -2;

  ELEM(mtx, row, col) = val;
  return 0;
}

/* Sets the reference val to the value of the (row, col) 
 * element of mtx.  Returns 0 if successful, -1 if either 
 * mtx or val is NULL, and -2 if row or col are outside of 
 * the dimensions of mtx.
 */
int getElement(struct matrix * mtx, int row, int col, 
               double * val) {
  if (!mtx || !val) return -1;
  assert (mtx->data);
  if (row <= 0 || row > mtx->rows ||
      col <= 0 || col > mtx->cols)
    return -2;

  *val = ELEM(mtx, row, col);
  return 0;
}

/* Sets the reference n to the number of rows of mtx.
 * Returns 0 if successful and -1 if mtx or n is NULL.
 */
int nRows(struct matrix * mtx, int * n) {
  if (!mtx || !n) return -1;
  *n = mtx->rows;
  return 0;
}

/* Sets the reference n to the number of columns of mtx.
 * Returns 0 if successful and -1 if mtx is NULL.
 */
int nCols(struct matrix * mtx, int * n) {
  if (!mtx || !n) return -1;
  *n = mtx->rows;
  return 0;
}

/* Prints the matrix to stdout.  Returns 0 if successful 
 * and -1 if mtx is NULL.
 */
int printMatrix(struct matrix * mtx) {
  if (!mtx) return -1;
  
  int row, col;
  for (row = 1; row <= mtx->rows; row++) {
    for (col = 1; col <= mtx->cols; col++) {
      // Print the floating-point element with
      //  - either a - if negative or a space if positive
      //  - at least 3 spaces before the .
      //  - precision to the hundredths place
      printf("%d ", (int)ELEM(mtx, row, col));
    }
    // separate rows by newlines
    printf("\n");
  }
  return 0;
}

/* Writes the transpose of matrix in into matrix out.  
 * Returns 0 if successful, -1 if either in or out is NULL,
 * and -2 if the dimensions of in and out are incompatible.
 */
int transpose(struct matrix * in, struct matrix * out) {
  if (!in || !out) return -1;
  if (in->rows != out->cols || in->cols != out->rows)
    return -2;

  int row, col;
  for (row = 1; row <= in->rows; row++)
    for (col = 1; col <= in->cols; col++)
      ELEM(out, col, row) = ELEM(in, row, col);
  return 0;
}

/* Writes the sum of matrices mtx1 and mtx2 into matrix 
 * sum. Returns 0 if successful, -1 if any of the matrices 
 * are NULL, and -2 if the dimensions of the matrices are
 * incompatible.
 */
int sum(struct matrix * mtx1, struct matrix * mtx2, struct matrix * sum) {
  if (!mtx1 || !mtx2 || !sum) return -1;
  if (mtx1->rows != mtx2->rows ||
      mtx1->rows != sum->rows ||
      mtx1->cols != mtx2->cols ||
      mtx1->cols != sum->cols)
    return -2;

  int row, col;
  for (col = 1; col <= mtx1->cols; col++)
    for (row = 1; row <= mtx1->rows; row++)
      ELEM(sum, row, col) = 
        ELEM(mtx1, row, col) + ELEM(mtx2, row, col);
  return 0;
}

/* Writes the product of matrices mtx1 and mtx2 into matrix
 * prod.  Returns 0 if successful, -1 if any of the 
 * matrices are NULL, and -2 if the dimensions of the 
 * matrices are incompatible.
 */
int product(struct matrix * mtx1, struct matrix * mtx2, struct matrix * prod) {
  if (!mtx1 || !mtx2 || !prod) return -1;
  if (mtx1->cols != mtx2->rows ||
      mtx1->rows != prod->rows ||
      mtx2->cols != prod->cols)
    return -2;

  int row, col, k;
  for (col = 1; col <= mtx2->cols; col++)
    for (row = 1; row <= mtx1->rows; row++) {
      double val = 0.0;
      for (k = 1; k <= mtx1->cols; k++)
        val += ELEM(mtx1, row, k) * ELEM(mtx2, k, col);
      ELEM(prod, row, col) = val;
    }
  return 0;
}

/* Writes the dot product of vectors v1 and v2 into 
 * reference prod.  Returns 0 if successful, -1 if any of
 * v1, v2, or prod are NULL, -2 if either matrix is not a 
 * vector, and -3 if the vectors are of incompatible 
 * dimensions.
 */
int dotProduct(struct matrix * v1, struct matrix * v2, double * prod) {
  if (!v1 || !v2 || !prod) return -1;
  if (v1->cols != 1 || v2->cols != 1) return -2;
  if (v1->rows != v2->rows) return -3;

  *prod = 0;
  int i;
  for (i = 1; i <= v1->rows; i++)
    *prod += ELEM(v1, i, 1) * ELEM(v2, i, 1);
  return 0;
}

int identity(struct matrix * m) {
  if (!m || m->rows != m->cols) return -1;
  int row, col;
  for (col = 1; col <= m->cols; col++)
    for (row = 1; row <= m->rows; row++)
      if (row == col) 
        ELEM(m, row, col) = 1.0;
      else 
        ELEM(m, row, col) = 0.0;
  return 0;
}

int isSquare(struct matrix * mtx) {
  return mtx && mtx->rows == mtx->cols;
}

int isDiagonal(struct matrix * mtx) {
  if (!isSquare(mtx)) return 0;
  int row, col;
  for (col = 1; col <= mtx->cols; col++)
    for (row = 1; row <= mtx->rows; row++)
      // if the element is not on the diagonal and not 0
      if (row != col && ELEM(mtx, row, col) != 0.0)
        // then the matrix is not diagonal
        return 0;
  return 1;
}

int isUpperTriangular(struct matrix * mtx) {
  if (!isSquare(mtx)) return 0;
  int row, col;
  // looks at positions below the diagonal
  for (col = 1; col <= mtx->cols; col++)
    for (row = col+1; row <= mtx->rows; row++) 
      if (ELEM(mtx, row, col) != 0.0)
        return 0;
  return 1;
}

int diagonal(struct matrix * v, struct matrix * mtx) {
  if (!v || !mtx ||
      v->cols > 1 || v->rows != mtx->rows ||
      mtx->cols != mtx->rows)
    return -1;
  int row, col;
  for (col = 1; col <= mtx->cols; col++)
    for (row = 1; row <= mtx->rows; row++)
      if (row == col) 
        ELEM(mtx, row, col) = ELEM(v, col, 1);
      else
        ELEM(mtx, row, col) = 0.0;
  return 0;
}


