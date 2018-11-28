#ifndef METRICS_H_
#define METRICS_H_

#include <math.h>
#include "matrix.h"

void mean_square_vector(double *result, double *predicted, double *real,
                        int size);

double mean_square_error(Matrix *network_results, Matrix *real_y);
#endif