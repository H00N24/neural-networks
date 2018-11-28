#include "metrics.h"

void mean_square_vector(double *result, double *predicted, double *real,
                        int size) {
  for (int i = 0; i < size; i++) {
    *(result + i) = pow(*(predicted + i) - *(real + i), 2);
  }
}

double mean_square_error(Matrix *network_results, Matrix *real_y) {
  double result = 0;
  for (int i = 0; i < real_y->n; i++) {
    result += pow(network_results->data[0][i] - real_y->data[0][i], 2);
  }
  return result / (double)real_y->n;
}