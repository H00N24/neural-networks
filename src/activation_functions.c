#include "activation_functions.h"

void sigmoid(double *result, double *values, int size)
{
    for (int i = 0; i < size; i++)
    {
        *(result + i) = 1 / (1 + exp(-*(values + i)));
    }
}

void sigmoid_prime(double *result, double *values, int size)
{
    double sigm;
    for (int i = 0; i < size; i++)
    {
        sigm = 1 / (1 + exp(-*(values + i)));
        *(result + i) = sigm * (1 - sigm);
    }
}