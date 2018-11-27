#ifndef ACTIVATION_FUNCTIONS_
#define ACTIVATION_FUNCTIONS_

#include <math.h>

#include "matrix.h"

double sigmoid(double value);

double sigmoid_prime(double value);

double relu(double value);

double relu_prime(double value);

#endif