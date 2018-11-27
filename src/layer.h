#ifndef LAYER_H_
#define LAYER_H_

#include <stdlib.h>

#include "matrix.h"

typedef struct layer_obj {
  unsigned int neurons;
  unsigned int inputs;
  unsigned int outputs;

  Matrix *weights;
  Matrix *z;
  Matrix *a;

  void (*activation)();
  void (*activation_prime)();
} Layer;

Layer *layer_init(int neurons, int inputs, int outputs, void (*activation)(),
                  void (*activation_prime)());

void layer_free(Layer *layer);

void weights_init(Layer *layer, void (*initializer)(Matrix *, int, int));

#endif