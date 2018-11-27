#include "activation_functions.h"

double sigmoid(double value) { return 1 / (1 + exp(-value)); }

double sigmoid_prime(double value) {
  return sigmoid(value) * sigmoid(1.0 - value);
}

double relu(double value) { return (value > 0) ? value : 0; }

double relu_prime(double value) { return (value > 0) ? 1 : 0; }