
#ifndef UTILS_H_
#define UTILS_H_

#include <math.h>
#include <stdlib.h>

#include "matrix.h"

void shuffle_array(int *array, int n);
int array_max_index(double *array, int n);

void initializer_GB(Matrix *weights, int inputs, int outputs);

void train_test_split(Matrix *all_data, Matrix *all_labels, Matrix **train_data,
                      Matrix **train_labels, Matrix **test_data,
                      Matrix **test_labels);

#endif