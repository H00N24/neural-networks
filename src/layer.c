#include "layer.h"

Layer *layer_init(int neurons, int inputs, int outputs,
                  double (*activation)(double),
                  double (*activation_prime)(double)) {
  Layer *new_layer = (Layer *)malloc(sizeof(struct layer_obj));

  new_layer->neurons = neurons;
  new_layer->inputs = inputs;
  new_layer->outputs = outputs;
  new_layer->activation = activation;
  new_layer->activation_prime = activation_prime;

  new_layer->weights = matrix_init(1 + new_layer->inputs, new_layer->neurons);
  new_layer->z = matrix_init(1, new_layer->neurons);
  new_layer->a = matrix_init(1, 1 + new_layer->neurons);

  return new_layer;
}

void layer_free(Layer *layer) {
  matrix_free(layer->weights);
  matrix_free(layer->z);
  matrix_free(layer->a);

  free(layer);
}

void weights_init(Layer *layer, void (*initializer)(Matrix *, int, int)) {
  initializer(layer->weights, layer->inputs, layer->outputs);
}
