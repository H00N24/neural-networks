#include "metrics.h"

double mean_square_error(Matrix *network_results, Matrix *real_y) {
  double result = 0;
  for (int i = 0; i < real_y->n; i++) {
    result += pow(network_results->data[0][i] - real_y->data[0][i], 2);
  }
  return result / (double)real_y->n;
}