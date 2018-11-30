#include "utils.h"

double randn(double mu, double sigma) {
  double U1, U2, W, mult;
  static double X1, X2;
  static int call = 0;

  if (call == 1) {
    call = !call;
    return (mu + sigma * (double)X2);
  }

  do {
    U1 = -1 + ((double)rand() / RAND_MAX) * 2;
    U2 = -1 + ((double)rand() / RAND_MAX) * 2;
    W = pow(U1, 2) + pow(U2, 2);
  } while (W >= 1 || W == 0);

  mult = sqrt((-2 * log(W)) / W);
  X1 = U1 * mult;
  X2 = U2 * mult;

  call = !call;

  return (mu + sigma * (double)X1);
}

void shuffle_array(int *array, int n) {
  for (int i = 0; i < n - 1; i++) {
    size_t j = i + rand() / (RAND_MAX / (n - i) + 1);
    int t = array[j];
    array[j] = array[i];
    array[i] = t;
  }
}

int array_max_index(double *array, int n) {
  int k = 0;
  double max = array[k];

  for (int i = 0; i < n; ++i) {
    if (array[i] > max) {
      max = array[i];
      k = i;
    }
  }
  return k;
}

void initializer_GB(Matrix *weights, int inputs, int outputs) {
  // Gloriot & Bengio initialization
  double mn = sqrt(6 / (double)(inputs + outputs));
  for (int i = 0; i < weights->m; i++) {
    for (int j = 0; j < weights->n; j++) {
      weights->data[i][j] = randn(0, 1) * mn;
    }
  }
}
