#include "network.h"

Network *network_init(int num_of_layers) {
  Network *new_network = malloc(sizeof(struct network_obj));

  new_network->num_of_layers = num_of_layers;
  new_network->layers = malloc(num_of_layers * sizeof(Layer *));

  return new_network;
}

void network_free(Network *network) {
  for (int i = 0; i < network->num_of_layers; ++i) {
    layer_free(network->layers[i]);
  }
  free(network->layers);
  free(network);
}

Network *final_architecture() {
  Network *network = network_init(2);
  network->layers[0] =
      layer_init(HIDDEN_L, INPUT_L, OUTPUT_L, relu, relu_prime);

  network->layers[1] =
      layer_init(OUTPUT_L, HIDDEN_L, 10, sigmoid, sigmoid_prime);

  for (int i = 0; i < network->num_of_layers; i++) {
    weights_init(network->layers[i], initializer_GB);
  }

  return network;
}

int forward_pass(Network *network, Matrix *X, Matrix *y) {
  for (int i = 0; i < network->num_of_layers; i++) {
    matrix_multiplication(network->layers[i]->z,
                          (i == 0) ? X : network->layers[i - 1]->a,
                          network->layers[i]->weights, true);
    matrix_apply(network->layers[i]->a, network->layers[i]->z,
                 network->layers[i]->activation);

    Matrix *a = network->layers[i]->a;
    a->data[0][a->n - 1] = 1;
  }

  return array_max_index(
      network->layers[network->num_of_layers - 1]->a->data[0], y->n);
}

void backward_pass(Network *network, Matrix *X, Matrix *y) {
  Matrix *X_T = matrix_init_empty(X->n, X->m);
  matrix_transpose_line(X_T, X);

  for (int i = network->num_of_layers - 1; i >= 0; i--) {
    if (i == network->num_of_layers - 1) {
      mean_square_prime(network->layers[i]->d_a, network->layers[i]->a, y);
    } else {
      matrix_multiplication(network->layers[i]->d_a_T,
                            network->layers[i + 1]->weights,
                            network->layers[i + 1]->d_z_T /*Transpose*/, true);
    }

    matrix_apply(network->layers[i]->d_z, network->layers[i]->z,
                 network->layers[i]->activation_prime);

    matrix_prod(network->layers[i]->d_z, network->layers[i]->d_a,
                network->layers[i]->d_z);

    if (i != 0) {
      matrix_multiplication(network->layers[i]->d_weights,
                            network->layers[i - 1]->a_T /*Transpose*/,
                            network->layers[i]->d_z, false);
    } else {
      matrix_multiplication(network->layers[i]->d_weights, X_T /*Transpose*/,
                            network->layers[i]->d_z, false);
    }
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
}

inline void backprop(Network *network, Matrix *X, Matrix *y) {
  forward_pass(network, X, y);
  backward_pass(network, X, y);
}

double network_accuracy(Network *network, Matrix *test_data,
                        Matrix *test_labels, char *output_file_name) {
  int predicted, good, bad;
  good = 0;
  bad = 0;
  Matrix *X = matrix_init_empty(1, test_data->n);
  Matrix *y = matrix_init_empty(1, test_labels->n);
  FILE *output_file = NULL;
  if (output_file_name != NULL) {
    output_file = fopen(output_file_name, "w");
  }

  for (int i = 0; i < test_data->m; ++i) {
    X->data[0] = test_data->data[i];
    y->data[0] = test_labels->data[i];
    predicted = forward_pass(network, X, y);
    if (predicted == array_max_index(y->data[0], y->n))
      good++;
    else
      bad++;
    if (output_file != NULL) {
      fprintf(output_file, "%d\n", predicted);
    }
  }

  matrix_empty_free(X);
  matrix_empty_free(y);
  if (output_file_name != NULL && output_file != NULL) {
    fclose(output_file);
  }
  return good / (double)(good + bad) * 100;
}

void train_network(Network *network, int epochs, double training_rate,
                   double mini_batch_size, Matrix *train_data,
                   Matrix *train_labels, Matrix *eval_data,
                   Matrix *eval_labels) {
  DPRINT("\n==Training: Start==\n");
  DPRINT("%d epochs, %.3f training rate, %d batch size\n", epochs,
         training_rate, (int)mini_batch_size);
  DPRINT("Training data shape: (%d, %d)\n", train_data->m, train_data->n);
  DPRINT("Training labels shape: (%d, %d)\n", train_labels->m, train_labels->n);
  DPRINT("Eval data shape: (%d, %d)\n", eval_data->m, eval_data->n);
  DPRINT("Eval labels shape: (%d, %d)\n", eval_labels->m, eval_labels->n);
  Matrix *X = matrix_init_empty(1, train_data->n);
  Matrix *y = matrix_init_empty(1, train_labels->n);

  for (int j = 0; j < epochs; j++) {
    DPRINT("Epoch %d: 000%%", j + 1);
    DTIME_START_COUNTER;
    for (int i = 0; i < train_data->m; i++) {
      X->data[0] = train_data->data[i];
      y->data[0] = train_labels->data[i];

      backprop(network, X, y);

      if (i % (int)mini_batch_size == 0 || i == train_data->m - 1) {
        DPRINT("\b\b\b\b%03.0f%%", i * 100 / (double)(train_data->m - 1));
        apply_derivation(network, mini_batch_size, training_rate);
      }
    }
    DPRINT("\n  Time: %.2fs\n", DTIME_DURATION);
    DPRINT("  Eval accuracy: %.2f%%\n",
           network_accuracy(network, eval_data, eval_labels, NULL));
  }
  matrix_empty_free(X);
  matrix_empty_free(y);
  DPRINT("==Training: End==\n");
}