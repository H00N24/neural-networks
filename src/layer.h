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

  double (*activation)(double);
  double (*activation_prime)(double);
} Layer;

Layer *layer_init(int neurons, int inputs, int outputs,
                  double (*activation)(double),
                  double (*activation_prime)(double));

void layer_free(Layer *layer);

void weights_init(Layer *layer, void (*initializer)(Matrix *, int, int));

#endif