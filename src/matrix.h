#ifndef MATRIX_H_
#define MATRIX_H_

#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct matrix_obj {
  int m;
  int n;
  double **data;
} Matrix;

Matrix *matrix_init(int m, int n);

void matrix_free(Matrix *matrix);

void matrix_multiplication(Matrix *result, Matrix *matrix_1, Matrix *matrix_2,
                           bool zero_init);

void matrix_sum(Matrix *result, Matrix *matrix_1, Matrix *matrix_2);

void matrix_prod(Matrix *result, Matrix *matrix_1, Matrix *matrix_2);

double sum_of_matrix(Matrix *matrix);

void print_matrix(Matrix *matrix, bool int_out);

#endif