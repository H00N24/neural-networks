#include "matrix.h"

Matrix *matrix_init(int m, int n) {
  // Initialize struct matrix_obj
  Matrix *new_matrix = (Matrix *)malloc(sizeof(struct matrix_obj));

  // Initialize data in matrix_obj
  new_matrix->data = (double **)malloc(m * sizeof(double *));
  for (int i = 0; i < m; i++) {
    new_matrix->data[i] = (double *)malloc(n * sizeof(double));
  }

  new_matrix->m = m;
  new_matrix->n = n;

  return new_matrix;
}

void matrix_free(Matrix *matrix) {
  for (int i = 0; i < matrix->m; i++) free(matrix->data[i]);

  free(matrix->data);
  free(matrix);
}

void matrix_multiplication(Matrix *result, Matrix *matrix_1, Matrix *matrix_2,
                           char zero_init) {
  for (int i = 0; i < matrix_1->m; i++) {
    for (int j = 0; j < matrix_2->n; j++) {
      if (zero_init) result->data[i][j] = 0;
      for (int x = 0; x < matrix_1->n; x++) {
        result->data[i][j] += matrix_1->data[i][x] * matrix_2->data[x][j];
      }
    }
  }
}

void matrix_sum(Matrix *result, Matrix *matrix_1, Matrix *matrix_2) {
  for (int i = 0; i < result->m; i++) {
    for (int j = 0; j < result->n; j++) {
      result->data[i][j] = matrix_1->data[i][j] + matrix_2->data[i][j];
    }
  }
}

void matrix_prod(Matrix *result, Matrix *matrix_1, Matrix *matrix_2) {
  for (int i = 0; i < result->m; i++) {
    for (int j = 0; j < result->n; j++) {
      result->data[i][j] = matrix_1->data[i][j] * matrix_2->data[i][j];
    }
  }
}

double sum_of_matrix(Matrix *matrix) {
  double result = 0;
  for (int i = 0; i < matrix->m; i++) {
    for (int j = 0; j < matrix->n; j++) {
      result += matrix->data[i][j];
    }
  }
  return result;
}

void print_matrix(Matrix *matrix) {
  for (int i = 0; i < matrix->m; i++) {
    for (int j = 0; j < matrix->n; j++) {
      printf("%.2e", matrix->data[i][j]);
      if (j < matrix->n - 1) {
        printf(",");
      }
    }
    printf("\n");
  }
}