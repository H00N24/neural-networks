#ifndef MATRIX_H_
#define MATRIX_H_

#include <math.h>
#include <stdio.h>

typedef struct matrix_obj {
  int m;
  int n;
  double **data;
} Matrix;

Matrix *matrix_init(int m, int n);
void matrix_free(Matrix *matrix);

void matrix_multiplication(double *result, double *matrix_1, int m1, int n1,
                           double *matrix_2, int m2, int n2, char zero_init);

void matrix_sum(double *result, double *matrix_1, double *matrix_2, int m,
                int n);

void matrix_prod(double *result, double *matrix_1, double *matrix_2, int m,
                 int n);

void matrix_prod(double *result, double *matrix_1, double *matrix_2, int m,
                 int n);

double sum_of_matrix(double *matrix, int m, int n);

void print_matrix(double *matrix, int m, int n);

#endif