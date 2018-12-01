#include "network.h"

Network *network_init(int num_of_layers) {
  Network *new_network = malloc(sizeof(struct network_obj));

  new_network->num_of_layers = num_of_layers;
  new_network->good = 0;
  new_network->bad = 0;

  new_network->layers = malloc(num_of_layers * sizeof(Layer *));

  return new_network;
}

void forward_pass(Network *network, Matrix *X, Matrix *y) {
  for (int i = 0; i < network->num_of_layers; i++) {
    matrix_multiplication(network->layers[i]->z,
                          (i == 0) ? X : network->layers[i - 1]->a,
                          network->layers[i]->weights, true);
    matrix_apply(network->layers[i]->a, network->layers[i]->z,
                 network->layers[i]->activation);

    Matrix *a = network->layers[i]->a;
    a->data[0][a->n - 1] = 1;
  }

  if (array_max_index(network->layers[network->num_of_layers - 1]->a->data[0],
                      y->n) == array_max_index(y->data[0], y->n)) {
    network->good++;
  } else {
    network->bad++;
  }
}

void backward_pass(Network *network, Matrix *X, Matrix *y) {
  Matrix *X_T = matrix_init_empty(X->n, X->m);
  matrix_transpose(X_T, X);
  DPRINT("Start of backprop\n");

  for (int i = network->num_of_layers - 1; i >= 0; i--) {
    DPRINT("Layer %d\n", i);

    if (i == network->num_of_layers - 1) {
      mean_square_prime(network->layers[i]->d_a, network->layers[i]->a, y);
    } else {
      matrix_multiplication(network->layers[i]->d_a_T,
                            network->layers[i + 1]->weights,
                            network->layers[i + 1]->d_z_T /*Transpose*/, true);
    }
    DPRINT("  d_a OK: %f\n", sum_of_matrix(network->layers[i]->d_a));

    matrix_apply(network->layers[i]->d_z, network->layers[i]->z,
                 network->layers[i]->activation_prime);
    DPRINT("  d_z 1 OK\n");

    matrix_prod(network->layers[i]->d_z, network->layers[i]->d_a,
                network->layers[i]->d_z);

    DPRINT("  d_z 2 OK\n");

    if (i != 0) {
      matrix_multiplication(network->layers[i]->d_weights,
                            network->layers[i - 1]->a_T /*Transpose*/,
                            network->layers[i]->d_z, false);
    } else {
      matrix_multiplication(network->layers[i]->d_weights, X_T /*Transpose*/,
                            network->layers[i]->d_z, false);
    }
    DPRINT("  d_weights OK\n");
  }

  matrix_empty_free(X_T);
}

void apply_derivation(Network *network, double examples, double step_size) {
  for (int i = 0; i < network->num_of_layers; i++) {
    matrix_times(network->layers[i]->d_weights, network->layers[i]->d_weights,
                 -step_size / examples);
    matrix_sum(network->layers[i]->weights, network->layers[i]->weights,
               network->layers[i]->d_weights);

    matrix_times(network->layers[i]->d_weights, network->layers[i]->d_weights,
                 0.0);
  }
  network->good = 0;
  network->bad = 0;
}
