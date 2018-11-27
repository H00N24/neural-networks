#include "CuTest.h"
#include "unit_test.h"

int main(void)
{
    CuString* output = CuStringNew();
    CuSuite* suite = CuSuiteNew();

    CuSuite* matrix_suite = GetSuiteMatrix();
    CuSuiteAddSuite(suite, matrix_suite);

    CuSuiteRun(suite);
    CuSuiteSummary(suite, output);
    CuSuiteDetails(suite, output);
    printf("%s\n", output->buffer);

    /*
    free(output->buffer);
    free(output);

    for (int i = 0; i < matrix_suite->count; i++)
    {
        free(matrix_suite->list[i]->name);
        free(matrix_suite->list[i]->jumpBuf);
    }
    free(matrix_suite);
    free(suite);
    */
}
