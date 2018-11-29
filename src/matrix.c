#include "matrix.h"

Matrix *matrix_init(int m, int n, bool zero_init) {
  // Initialize struct matrix_obj
  Matrix *new_matrix = (Matrix *)malloc(sizeof(Matrix));

  // Initialize data in matrix_obj
  new_matrix->data = (double **)malloc(m * sizeof(double *));
  for (int i = 0; i < m; i++) {
    new_matrix->data[i] = (double *)malloc(n * sizeof(double));
  }

  new_matrix->m = m;
  new_matrix->n = n;

  if (zero_init) {
    for (int i = 0; i < new_matrix->n; i++)
      for (int j = 0; j < new_matrix->m; j++) new_matrix->data[i][j] = 0;
  }

  return new_matrix;
}

Matrix *matrix_init_empty(int m, int n) {
  Matrix *new_matrix = (Matrix *)malloc(sizeof(Matrix));

  new_matrix->data = (double **)malloc(m * sizeof(double *));
  new_matrix->m = m;
  new_matrix->n = n;

  return new_matrix;
}

void matrix_free(Matrix *matrix) {
  for (int i = 0; i < matrix->m; i++) free(matrix->data[i]);

  free(matrix->data);
  free(matrix);
}

void matrix_empty_free(Matrix *matrix) {
  free(matrix->data);
  free(matrix);
}

void matrix_multiplication(Matrix *result, Matrix *matrix_1, Matrix *matrix_2,
                           bool zero_init) {
  // (m x n) * (n x p) = (m x p)
#ifdef DEBUG
  if (matrix_1->n != matrix_2->m) {
    printf("mat_1->N '%d' != mat_2->M '%d', matrix_multiplication", matrix_1->n,
           matrix_2->m);
    assert(matrix_1->n != matrix_2->m);
  }

  if (result->m != matrix_1->m) {
    printf("res->M '%d' != mat_1->M '%d', matrix_multiplication", result->m,
           matrix_1->m);
    assert(result->m == matrix_1->m);
  }

  if (result->n != matrix_2->n) {
    printf("res->N '%d' != mat_2->N '%d', matrix_multiplication", result->n,
           matrix_2->n);
    assert(result->n == matrix_2->n);
  }
#endif

  for (int i = 0; i < result->m; i++) {
    for (int j = 0; j < result->n; j++) {
      if (zero_init) result->data[i][j] = 0;
      for (int x = 0; x < matrix_1->n; x++) {
        result->data[i][j] += matrix_1->data[i][x] * matrix_2->data[x][j];
      }
    }
  }
}

void matrix_sum(Matrix *result, Matrix *matrix_1, Matrix *matrix_2) {
#ifdef DEBUG
  if (matrix_1->m < result->m) {
    printf("mat_1->M '%d' < res->M '%d', matrix_sum", matrix_1->m, result->m);
    assert(matrix_1->m >= result->m);
  }

  if (matrix_2->m < result->m) {
    printf("mat_2->M '%d' < res->M '%d', matrix_sum", matrix_2->m, result->m);
    assert(matrix_2->m >= result->m);
  }

  if (matrix_1->n < result->n) {
    printf("mat_1->N '%d' < res->N '%d', matrix_sum", matrix_1->n, result->n);
    assert(matrix_1->n >= result->n);
  }

  if (matrix_2->n < result->n) {
    printf("mat_2->N '%d' < res->N '%d', matrix_sum", matrix_2->n, result->n);
    assert(matrix_2->n >= result->n);
  }
#endif

  for (int i = 0; i < result->m; i++) {
    for (int j = 0; j < result->n; j++) {
      result->data[i][j] = matrix_1->data[i][j] + matrix_2->data[i][j];
    }
  }
}

void matrix_prod(Matrix *result, Matrix *matrix_1, Matrix *matrix_2) {
#ifdef DEBUG
  if (matrix_1->m < result->m) {
    printf("mat_1->M '%d' < res->M '%d', matrix_prod", matrix_1->m, result->m);
    assert(matrix_1->m >= result->m);
  }

  if (matrix_2->m < result->m) {
    printf("mat_2->M '%d' < res->M '%d', matrix_prod", matrix_2->m, result->m);
    assert(matrix_2->m >= result->m);
  }

  if (matrix_1->n < result->n) {
    printf("mat_1->N '%d' < res->N '%d', matrix_prod", matrix_1->n, result->n);
    assert(matrix_1->n >= result->n);
  }

  if (matrix_2->n < result->n) {
    printf("mat_2->N '%d' < res->N '%d', matrix_prod", matrix_2->n, result->n);
    assert(matrix_2->n >= result->n);
  }
#endif

  for (int i = 0; i < result->m; i++) {
    for (int j = 0; j < result->n; j++) {
      result->data[i][j] = matrix_1->data[i][j] * matrix_2->data[i][j];
    }
  }
}

void matrix_transpose(Matrix *res, Matrix *input) {
#ifdef DEBUG
  if (res->n != 1) {
    printf("res->N '%d' != 1 , matrix_transpose", res->n);
    assert(res->n == 1);
  }

  if (input->m != 1) {
    printf("input->M '%d' != 1 , matrix_transpose", input->m);
    assert(input->m == 1);
  }

  if (res->m != input->n) {
    printf("res->M '%d' != input->N '%d', matrix_transpose", res->m, input->m);
    assert(res->m == input->n);
  }
#endif

  for (int i = 0; i < input->n; i++) {
    res->data[i] = &input->data[0][i];
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

void matrix_apply(Matrix *result, Matrix *matrix, double (*function)(double)) {
  for (int i = 0; i < matrix->m; i++) {
    for (int j = 0; j < matrix->n; j++) {
      result->data[i][j] = function(matrix->data[i][j]);
    }
  }
}

void matrix_divide(Matrix *result, Matrix *matrix, double value) {
  for (int i = 0; i < matrix->m; i++) {
    for (int j = 0; j < matrix->n; j++) {
      result->data[i][j] = matrix->data[i][j] / value;
    }
  }
}

void print_matrix(Matrix *matrix, bool int_out) {
  for (int i = 0; i < matrix->m; i++) {
    for (int j = 0; j < matrix->n; j++) {
      if (int_out)
        printf("%d", (int)matrix->data[i][j]);
      else
        printf("%.2e", matrix->data[i][j]);
      if (j < matrix->n - 1) {
        printf(",");
      }
    }
    printf("\n");
  }
}