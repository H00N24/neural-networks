#include "metrics.h"

void mean_square_vector(double *result, double *predicted, double *real,
                        int size) {
  for (int i = 0; i < size; i++) {
    *(result + i) = pow(*(predicted + i) - *(real + i), 2);
  }
}