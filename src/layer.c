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

  new_layer->weights =
      matrix_init(1 + new_layer->inputs, new_layer->neurons, false);
  new_layer->z = matrix_init(1, new_layer->neurons, false);
  new_layer->a = matrix_init(1, 1 + new_layer->neurons, false);

  new_layer->d_weights =
      matrix_init(new_layer->weights->m, new_layer->weights->n, true);
  new_layer->d_z = matrix_init(new_layer->z->m, new_layer->z->n, false);
  new_layer->d_a = matrix_init(new_layer->a->m, new_layer->a->n, false);

  new_layer->a_T = matrix_init_empty(new_layer->a->n, new_layer->a->m);
  new_layer->d_z_T = matrix_init_empty(new_layer->d_z->n, new_layer->d_z->m);
  new_layer->d_a_T = matrix_init_empty(new_layer->d_a->n, new_layer->d_a->m);

  matrix_transpose(new_layer->a_T, new_layer->a);
  matrix_transpose(new_layer->d_z_T, new_layer->d_z);
  matrix_transpose(new_layer->d_a_T, new_layer->d_a);

  return new_layer;
}

void layer_free(Layer *layer) {
  matrix_free(layer->weights);
  matrix_free(layer->z);
  matrix_free(layer->a);

  matrix_free(layer->d_weights);
  matrix_free(layer->d_z);
  matrix_free(layer->d_a);

  matrix_empty_free(layer->a_T);
  matrix_empty_free(layer->d_z_T);
  matrix_empty_free(layer->d_a_T);

  free(layer);
}

void weights_init(Layer *layer, void (*initializer)(Matrix *, int, int)) {
  initializer(layer->weights, layer->inputs, layer->outputs);
}
