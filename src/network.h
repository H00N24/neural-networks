#ifndef NETWORK_H_
#define NETWORK_H_

#include "activation_functions.h"
#include "data_loader.h"
#include "debug.h"
#include "matrix.h"
#include "metrics.h"
#include "utils.h"

#define INPUT_L 28 * 28
#define HIDDEN_L 300
#define OUTPUT_L 10

typedef struct HiddenLayer {
  unsigned int neurons;
  unsigned int inputs;
  unsigned int outputs;
  double weights[1 + INPUT_L][HIDDEN_L];
  double z[1][HIDDEN_L];
  double a[1][HIDDEN_L + 1];
  void (*activation)();
  void (*activation_prime)();
} HiddenLayer;

typedef struct OutputLayer {
  unsigned int neurons;
  unsigned int inputs;
  unsigned int outputs;
  double weights[1 + HIDDEN_L][OUTPUT_L];
  double z[1][OUTPUT_L];
  double a[1][OUTPUT_L];
  void (*activation)();
  void (*activation_prime)();
} OutputLayer;

double training_data[60000][1 + INPUT_L];
double training_labels[60000][OUTPUT_L];

#endif