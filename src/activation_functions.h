#ifndef ACTIVATION_FUNCTIONS_
#define ACTIVATION_FUNCTIONS_

#include <math.h>

void sigmoid(double *result, double *values, int size);

void sigmoid_prime(double *result, double *values, int size);

#endif