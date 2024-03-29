#include "unit_test.h"

/*---------------------------------------------------------*
 * Helper functions
 *---------------------------------------------------------*/
void matrix_fill(Matrix *mat) {
  int count = 0;
  for (int i = 0; i < mat->m; ++i) {
    for (int j = 0; j < mat->n; ++j) {
      mat->data[i][j] = ++count;
    }
  }
}

/*---------------------------------------------------------*
 * Matrix Test
 *---------------------------------------------------------*/
void TestMatrixInit(CuTest *tc) {
  Matrix *mat = matrix_init_full(5, 3);
  CuAssertIntEquals(tc, 5, mat->m);
  CuAssertIntEquals(tc, 3, mat->n);

  matrix_fill(mat);

  CuAssertIntEquals(tc, 1, mat->data[0][0]);
  CuAssertIntEquals(tc, 3, mat->data[0][2]);
  CuAssertIntEquals(tc, 7, mat->data[2][0]);
  CuAssertIntEquals(tc, 15, mat->data[4][2]);

  matrix_full_free(mat);
}

void TestMatrix_ZeroInit(CuTest *tc) {
  Matrix *mat = matrix_init_full(5, 4);
  CuAssertIntEquals(tc, 5, mat->m);
  CuAssertIntEquals(tc, 4, mat->n);

  for (int i = 0; i < mat->n; i++)
    for (int j = 0; j < mat->m; j++) CuAssertIntEquals(tc, 0, mat->data[i][j]);

  matrix_full_free(mat);
}

void TestMatrixInitEmpty(CuTest *tc) {
  Matrix *vector = matrix_init_empty(4, 4);
  Matrix *mat = matrix_init_full(4, 4);

  matrix_fill(mat);

  for (int i = 0; i < vector->m; i++) {
    vector->data[i] = mat->data[i];
  }

  CuAssertIntEquals(tc, 1, vector->data[0][0]);
  CuAssertIntEquals(tc, 5, vector->data[1][0]);
  CuAssertIntEquals(tc, 8, vector->data[1][3]);
  CuAssertIntEquals(tc, 10, vector->data[2][1]);
  CuAssertIntEquals(tc, 16, vector->data[3][3]);

  matrix_full_free(mat);
  matrix_empty_free(vector);
}

void TestMatrixMultiplication_ZeroInit(CuTest *tc) {
  Matrix *mat_1 = matrix_init_full(4, 4);
  Matrix *mat_2 = matrix_init_full(4, 4);
  matrix_fill(mat_1);
  matrix_fill(mat_2);

  Matrix *mat_res = matrix_init_full(4, 4);
  matrix_multiplication(mat_res, mat_1, mat_2, 1);

  CuAssertIntEquals(tc, 90, mat_res->data[0][0]);
  CuAssertIntEquals(tc, 202, mat_res->data[1][0]);
  CuAssertIntEquals(tc, 280, mat_res->data[1][3]);
  CuAssertIntEquals(tc, 356, mat_res->data[2][1]);
  CuAssertIntEquals(tc, 600, mat_res->data[3][3]);

  matrix_full_free(mat_1);
  matrix_full_free(mat_2);
  matrix_full_free(mat_res);
}

void TestMatrixMultiplication(CuTest *tc) {
  Matrix *mat_1 = matrix_init_full(4, 4);
  Matrix *mat_2 = matrix_init_full(4, 4);
  matrix_fill(mat_1);
  matrix_fill(mat_2);

  Matrix *mat_res = matrix_init_full(4, 4);
  matrix_fill(mat_res);
  matrix_multiplication(mat_res, mat_1, mat_2, 0);

  CuAssertIntEquals(tc, 91, mat_res->data[0][0]);
  CuAssertIntEquals(tc, 202 + 5, mat_res->data[1][0]);
  CuAssertIntEquals(tc, 280 + 8, mat_res->data[1][3]);
  CuAssertIntEquals(tc, 356 + 10, mat_res->data[2][1]);
  CuAssertIntEquals(tc, 600 + 16, mat_res->data[3][3]);

  matrix_full_free(mat_1);
  matrix_full_free(mat_2);
  matrix_full_free(mat_res);
}

void TestMatrixMultiplication_DiffSizes(CuTest *tc) {
  Matrix *mat_1 = matrix_init_full(2, 4);
  Matrix *mat_2 = matrix_init_full(4, 3);
  matrix_fill(mat_1);
  matrix_fill(mat_2);

  Matrix *mat_res = matrix_init_full(2, 3);
  matrix_multiplication(mat_res, mat_1, mat_2, 1);

  CuAssertIntEquals(tc, 70, mat_res->data[0][0]);
  CuAssertIntEquals(tc, 80, mat_res->data[0][1]);
  CuAssertIntEquals(tc, 90, mat_res->data[0][2]);
  CuAssertIntEquals(tc, 158, mat_res->data[1][0]);
  CuAssertIntEquals(tc, 184, mat_res->data[1][1]);
  CuAssertIntEquals(tc, 210, mat_res->data[1][2]);

  matrix_full_free(mat_1);
  matrix_full_free(mat_2);
  matrix_full_free(mat_res);
}

void TestMatrixSum(CuTest *tc) {
  Matrix *mat_1 = matrix_init_full(4, 4);
  Matrix *mat_2 = matrix_init_full(4, 4);
  matrix_fill(mat_1);
  matrix_fill(mat_2);

  Matrix *mat_res = matrix_init_full(4, 4);
  matrix_sum(mat_res, mat_1, mat_2);

  CuAssertIntEquals(tc, 1 + 1, mat_res->data[0][0]);
  CuAssertIntEquals(tc, 5 + 5, mat_res->data[1][0]);
  CuAssertIntEquals(tc, 8 + 8, mat_res->data[1][3]);
  CuAssertIntEquals(tc, 10 + 10, mat_res->data[2][1]);
  CuAssertIntEquals(tc, 16 + 16, mat_res->data[3][3]);

  matrix_full_free(mat_1);
  matrix_full_free(mat_2);
  matrix_full_free(mat_res);
}

void TestMatrixSum_DiffSizes(CuTest *tc) {
  Matrix *mat_1 = matrix_init_full(4, 3);
  Matrix *mat_2 = matrix_init_full(5, 4);
  matrix_fill(mat_1);
  matrix_fill(mat_2);

  Matrix *mat_res = matrix_init_full(2, 3);
  matrix_sum(mat_res, mat_1, mat_2);

  CuAssertIntEquals(tc, 2, mat_res->data[0][0]);
  CuAssertIntEquals(tc, 4, mat_res->data[0][1]);
  CuAssertIntEquals(tc, 6, mat_res->data[0][2]);
  CuAssertIntEquals(tc, 9, mat_res->data[1][0]);
  CuAssertIntEquals(tc, 11, mat_res->data[1][1]);
  CuAssertIntEquals(tc, 13, mat_res->data[1][2]);

  matrix_full_free(mat_1);
  matrix_full_free(mat_2);
  matrix_full_free(mat_res);
}

void TestMatrixProd(CuTest *tc) {
  Matrix *mat_1 = matrix_init_full(4, 4);
  Matrix *mat_2 = matrix_init_full(4, 4);
  matrix_fill(mat_1);
  matrix_fill(mat_2);

  Matrix *mat_res = matrix_init_full(4, 4);

  matrix_prod(mat_res, mat_1, mat_2);

  CuAssertIntEquals(tc, 1 * 1, mat_res->data[0][0]);
  CuAssertIntEquals(tc, 5 * 5, mat_res->data[1][0]);
  CuAssertIntEquals(tc, 8 * 8, mat_res->data[1][3]);
  CuAssertIntEquals(tc, 10 * 10, mat_res->data[2][1]);
  CuAssertIntEquals(tc, 16 * 16, mat_res->data[3][3]);

  matrix_full_free(mat_1);
  matrix_full_free(mat_2);
  matrix_full_free(mat_res);
}

void TestMatrixProd_DiffSizes(CuTest *tc) {
  Matrix *mat_1 = matrix_init_full(4, 3);
  Matrix *mat_2 = matrix_init_full(5, 4);
  matrix_fill(mat_1);
  matrix_fill(mat_2);

  Matrix *mat_res = matrix_init_full(2, 3);
  matrix_prod(mat_res, mat_1, mat_2);

  CuAssertIntEquals(tc, 1, mat_res->data[0][0]);
  CuAssertIntEquals(tc, 4, mat_res->data[0][1]);
  CuAssertIntEquals(tc, 9, mat_res->data[0][2]);
  CuAssertIntEquals(tc, 20, mat_res->data[1][0]);
  CuAssertIntEquals(tc, 30, mat_res->data[1][1]);
  CuAssertIntEquals(tc, 42, mat_res->data[1][2]);

  matrix_full_free(mat_1);
  matrix_full_free(mat_2);
  matrix_full_free(mat_res);
}

void TestMatrixTranspose(CuTest *tc) {
  Matrix *mat = matrix_init_full(1, 5);
  matrix_fill(mat);

  Matrix *res = matrix_init_empty(5, 1);
  matrix_transpose_line(res, mat);

  CuAssertIntEquals(tc, 1, res->data[0][0]);
  CuAssertIntEquals(tc, 2, res->data[1][0]);
  CuAssertIntEquals(tc, 3, res->data[2][0]);
  CuAssertIntEquals(tc, 4, res->data[3][0]);
  CuAssertIntEquals(tc, 5, res->data[4][0]);

  matrix_full_free(mat);
  matrix_empty_free(res);
}

void TestSumOfMatrix(CuTest *tc) {
  Matrix *mat = matrix_init_full(5, 3);
  matrix_fill(mat);

  double sum = sum_of_matrix(mat);
  CuAssertIntEquals(tc, 120, sum);

  matrix_full_free(mat);
}

CuSuite *GetSuiteMatrix(void) {
  CuSuite *suite = CuSuiteNew();

  SUITE_ADD_TEST(suite, TestMatrixInit);
  SUITE_ADD_TEST(suite, TestMatrix_ZeroInit);
  SUITE_ADD_TEST(suite, TestMatrixInitEmpty);
  SUITE_ADD_TEST(suite, TestMatrixMultiplication_ZeroInit);
  SUITE_ADD_TEST(suite, TestMatrixMultiplication);
  SUITE_ADD_TEST(suite, TestMatrixMultiplication_DiffSizes);
  SUITE_ADD_TEST(suite, TestMatrixSum);
  SUITE_ADD_TEST(suite, TestMatrixSum_DiffSizes);
  SUITE_ADD_TEST(suite, TestMatrixProd);
  SUITE_ADD_TEST(suite, TestMatrixProd_DiffSizes);
  SUITE_ADD_TEST(suite, TestMatrixTranspose);
  SUITE_ADD_TEST(suite, TestSumOfMatrix);

  return suite;
}
