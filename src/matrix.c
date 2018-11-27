#include "matrix.h"

void matrix_multiplication(double *result, double *matrix_1, int m1, int n1,
                           double *matrix_2, int m2, int n2, char zero_init) {
  for (int i = 0; i < m1; i++) {
    for (int j = 0; j < n2; j++) {
      if (zero_init) *((result + i * m1) + j) = 0;
      for (int x = 0; x < n1; x++) {
        *((result + i * m1) + j) +=
            *((matrix_1 + i * n1) + x) * *((matrix_2 + x * n2) + j);
      }
    }
  }
}

void matrix_sum(double *result, double *matrix_1, double *matrix_2, int m,
                int n) {
  for (int i = 0; i < m; i++) {
    for (int j = 0; j < n; i++) {
      *((result + i * m) + j) +=
          *((matrix_1 + i * m) + j) + *((matrix_2 + i * n) + j);
    }
  }
}

void matrix_prod(double *result, double *matrix_1, double *matrix_2, int m,
                 int n) {
  for (int i = 0; i < m; i++) {
    for (int j = 0; j < n; i++) {
      *((result + i * m) + j) +=
          *((matrix_1 + i * m) + j) * *((matrix_2 + i * n) + j);
    }
  }
}

double sum_of_matrix(double *matrix, int m, int n) {
  double resultult = 0;
  for (int i = 0; i < m; i++) {
    for (int j = 0; j < n; j++) {
      resultult += *((matrix + i * m) + j);
    }
  }
  return resultult;
}

void print_matrix(double *matrix, int m, int n) {
  for (int i = 0; i < m; i++) {
    for (int j = 0; j < n; j++) {
      printf("%d", (int)*((matrix + i * m) + j));
      if (j < n - 1) {
        printf(",");
      }
    }
    printf("\n");
  }
}