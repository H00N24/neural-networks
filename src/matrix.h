#ifndef MATRIX_H_
#define MATRIX_H_

#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "debug.h"

typedef struct matrix_obj {
  int m;
  int n;
  double **data;
} Matrix;

Matrix *matrix_init_lines(int m, int n);
Matrix *matrix_init_full(int m, int n);
Matrix *matrix_init_empty(int m, int n);

void matrix_lines_free(Matrix *matrix);
void matrix_full_free(Matrix *matrix);
void matrix_empty_free(Matrix *matrix);

void matrix_multiplication(Matrix *result, Matrix *matrix_1, Matrix *matrix_2,
                           bool zero_init);

void matrix_multi_transpose(Matrix *result, const Matrix *matrix,
                            const Matrix *matrix_T, bool zero_init);

void matrix_sum(Matrix *result, Matrix *matrix_1, Matrix *matrix_2);

void matrix_prod(Matrix *result, Matrix *matrix_1, Matrix *matrix_2);

void matrix_apply(Matrix *result, Matrix *matrix, double (*function)(double));

void matrix_times(Matrix *result, Matrix *matrix, double value);

void matrix_transpose_line(Matrix *res, const Matrix *input);
void matrix_transpose_full(Matrix *result, const Matrix *matrix);

double sum_of_matrix(Matrix *matrix);

void print_matrix(Matrix *matrix, bool int_out);

#endif