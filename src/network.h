#ifndef NETWORK_H_
#define NETWORK_H_

#include <stdbool.h>
#include <stdlib.h>
#include "error_functions.h"
#include "layer.h"
#include "matrix.h"
#include "utils.h"

typedef struct network_obj {
  int num_of_layers;
  int good;
  int bad;
  Layer **layers;

} Network;

Network *network_init(int num_of_layers);

void forward_pass(Network *network, Matrix *X, Matrix *y);
void backward_pass(Network *network, Matrix *X, Matrix *y);
void apply_derivation(Network *network, double examples, double step_size);
#endif