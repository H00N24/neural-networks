#include "utils.h"

double randn(double mu, double sigma)
{
    double U1, U2, W, mult;
    static double X1, X2;
    static int call = 0;

    if (call == 1)
    {
        call = !call;
        return (mu + sigma * (double)X2);
    }

    do
    {
        U1 = -1 + ((double)rand() / RAND_MAX) * 2;
        U2 = -1 + ((double)rand() / RAND_MAX) * 2;
        W = pow(U1, 2) + pow(U2, 2);
    } while (W >= 1 || W == 0);

    mult = sqrt((-2 * log(W)) / W);
    X1 = U1 * mult;
    X2 = U2 * mult;

    call = !call;

    return (mu + sigma * (double)X1);
}

void weights_initializer(double *weights, int m, int n, int inputs, int outputs)
{
    double mn = sqrt(6 / (double)(inputs + outputs));
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            *((weights + i * m) + j) = randn(0, 1) * mn;
        }
    }
}
