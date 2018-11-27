#include "unit_test.h"

/*---------------------------------------------------------*
 * Helper functions
 *---------------------------------------------------------*/
void matrix_fill(Matrix *mat)
{
    int count = 0;
    for (int i = 0; i < mat->m; ++i)
    {
        for (int j = 0; j < mat->n; ++j)
        {
            mat->data[i][j] = ++count;
        }
    }
}


/*---------------------------------------------------------*
 * Matrix Test
 *---------------------------------------------------------*/
void TestMatrixInit(CuTest* tc)
{
    Matrix *mat = matrix_init(5, 3);
    CuAssertIntEquals(tc, 5, mat->m);
    CuAssertIntEquals(tc, 3, mat->n);

    matrix_fill(mat);

    CuAssertIntEquals(tc, 1, mat->data[0][0]);
    CuAssertIntEquals(tc, 3, mat->data[0][2]);
    CuAssertIntEquals(tc, 7, mat->data[2][0]);
    CuAssertIntEquals(tc, 15, mat->data[4][2]);

    matrix_free(mat);
}

void TestMatrixMultiplication_ZeroUnit(CuTest* tc)
{
    Matrix *mat_1 = matrix_init(4, 4);
    Matrix *mat_2 = matrix_init(4, 4);
    matrix_fill(mat_1);
    matrix_fill(mat_2);

    Matrix *mat_res = matrix_init(4, 4);
    matrix_multiplication(mat_res, mat_1, mat_2, 1);

    CuAssertIntEquals(tc, 90, mat_res->data[0][0]);
    CuAssertIntEquals(tc, 202, mat_res->data[1][0]);
    CuAssertIntEquals(tc, 280, mat_res->data[1][3]);
    CuAssertIntEquals(tc, 356, mat_res->data[2][1]);
    CuAssertIntEquals(tc, 600, mat_res->data[3][3]);

    matrix_free(mat_1);
    matrix_free(mat_2);
    matrix_free(mat_res);
}

void TestMatrixMultiplication(CuTest* tc)
{
    Matrix *mat_1 = matrix_init(4, 4);
    Matrix *mat_2 = matrix_init(4, 4);
    matrix_fill(mat_1);
    matrix_fill(mat_2);

    Matrix *mat_res = matrix_init(4, 4);
    matrix_fill(mat_res);
    matrix_multiplication(mat_res, mat_1, mat_2, 0);

    CuAssertIntEquals(tc, 91, mat_res->data[0][0]);
    CuAssertIntEquals(tc, 202+5, mat_res->data[1][0]);
    CuAssertIntEquals(tc, 280+8, mat_res->data[1][3]);
    CuAssertIntEquals(tc, 356+10, mat_res->data[2][1]);
    CuAssertIntEquals(tc, 600+16, mat_res->data[3][3]);

    matrix_free(mat_1);
    matrix_free(mat_2);
    matrix_free(mat_res);
}

void TestMatrixSum(CuTest* tc)
{
    Matrix *mat_1 = matrix_init(4, 4);
    Matrix *mat_2 = matrix_init(4, 4);
    matrix_fill(mat_1);
    matrix_fill(mat_2);

    Matrix *mat_res = matrix_init(4, 4);
    matrix_sum(mat_res, mat_1, mat_2);

    CuAssertIntEquals(tc, 1+1, mat_res->data[0][0]);
    CuAssertIntEquals(tc, 5+5, mat_res->data[1][0]);
    CuAssertIntEquals(tc, 8+8, mat_res->data[1][3]);
    CuAssertIntEquals(tc, 10+10, mat_res->data[2][1]);
    CuAssertIntEquals(tc, 16+16, mat_res->data[3][3]);

    matrix_free(mat_1);
    matrix_free(mat_2);
    matrix_free(mat_res);
}

void TestMatrixProd(CuTest *tc)
{
    Matrix *mat_1 = matrix_init(4, 4);
    Matrix *mat_2 = matrix_init(4, 4);
    matrix_fill(mat_1);
    matrix_fill(mat_2);

    Matrix *mat_res = matrix_init(4, 4);

    matrix_prod(mat_res, mat_1, mat_2);

    CuAssertIntEquals(tc, 1*1, mat_res->data[0][0]);
    CuAssertIntEquals(tc, 5*5, mat_res->data[1][0]);
    CuAssertIntEquals(tc, 8*8, mat_res->data[1][3]);
    CuAssertIntEquals(tc, 10*10, mat_res->data[2][1]);
    CuAssertIntEquals(tc, 16*16, mat_res->data[3][3]);

    matrix_free(mat_1);
    matrix_free(mat_2);
    matrix_free(mat_res);
}

void TestSumOfMatrix(CuTest *tc)
{
    Matrix *mat = matrix_init(5, 3);
    matrix_fill(mat);

    double sum = sum_of_matrix(mat);
    CuAssertIntEquals(tc, 120, sum);

    matrix_free(mat);
}

CuSuite* GetSuiteMatrix(void)
{
    CuSuite* suite = CuSuiteNew();

    SUITE_ADD_TEST(suite, TestMatrixInit);
    SUITE_ADD_TEST(suite, TestMatrixMultiplication);
    SUITE_ADD_TEST(suite, TestMatrixMultiplication_ZeroUnit);
    SUITE_ADD_TEST(suite, TestMatrixSum);
    SUITE_ADD_TEST(suite, TestMatrixProd);
    SUITE_ADD_TEST(suite, TestSumOfMatrix);

    return suite;
}
