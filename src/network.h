#ifndef NETWORK_H_
#define NETWORK_H_

#include <stdbool.h>
#include <stdlib.h>
#include "layer.h"

typedef struct network_obj {
  int num_of_layers;
  Layer **layers;
} Network;

Network *network_init(int num_of_layers);

void forward_pass(Network *network, Matrix *X);

#endif