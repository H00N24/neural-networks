#include "network.h"

Network *network_init(int num_of_layers, int outputs) {
  Network *new_network = malloc(sizeof(struct network_obj));

  new_network->num_of_layers = num_of_layers;
  new_network->outputs = outputs;
  new_network->layers = malloc(num_of_layers * sizeof(Layer *));

  return new_network;
}

void forward_pass(Network *network, Matrix *X) {
  for (int i = 0; i < network->num_of_layers; i++) {
    matrix_multiplication(network->layers[i]->z,
                          (i == 0) ? X : network->layers[i - 1]->a,
                          network->layers[i]->weights, true);
    matrix_apply(network->layers[i]->a, network->layers[i]->z,
                 network->layers[i]->activation);

    Matrix *a = network->layers[i]->a;
    a->data[0][a->n - 1] = 1;
  }
}
