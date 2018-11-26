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

void relu(double *result, double *values, int size)
{
    for (int i = 0; i < size; i++)
    {
        *(result + i) = (*(values + i) > 0) ? *(values + i) : 0;
    }
}

void relu_prime(double *result, double *values, int size)
{
    for (int i = 0; i < size; i++)
    {
        *(result + i) = (*(values + i) > 0) ? 1 : 0;
    }
}