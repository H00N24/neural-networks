#include "error_functions.h"

void mean_square_prime(Matrix *result, Matrix *network_out, Matrix *y) {
  for (int i = 0; i < result->n; i++) {
    result->data[0][i] = 2 * (network_out->data[0][i] - y->data[0][i]);
  }
}