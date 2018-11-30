
#ifndef UTILS_H_
#define UTILS_H_

#include <math.h>
#include <stdlib.h>

#include "matrix.h"

void shuffle_array(int *array, int n);
int array_max_index(double *array, int n);

void initializer_GB(Matrix *weights, int inputs, int outputs);

#endif