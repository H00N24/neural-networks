#include "main.h"

#define INPUT_L 28 * 28
#define HIDDEN_L 300
#define OUTPUT_L 10

int main(int argc, char const *argv[]) {
  srand(42);

  Matrix *vectors = matrix_init(60000, 1 + INPUT_L, false);
  load_data(vectors, "../MNIST_DATA/mnist_train_vectors.csv", INPUT_L, true,
            scaler, 255.0);
  // print_matrix(vectors, false);
  Matrix *labels = matrix_init(60000, 10, false);
  load_data(labels, "../MNIST_DATA/mnist_train_labels.csv", 1, false,
            one_hot_encoder, 1);
  // print_matrix(labels, true);
  // return 0;
  // return 0;
  Network *network = network_init(2, 10);
  network->layers[0] = layer_init(HIDDEN_L, INPUT_L, 10, relu, relu_prime);

  network->layers[1] =
      layer_init(OUTPUT_L, HIDDEN_L, 10, sigmoid, sigmoid_prime);

  for (int i = 0; i < network->num_of_layers; i++) {
    weights_init(network->layers[i], initializer_GB);
  }

  Matrix *X = matrix_init_empty(1, 1 + 28 * 28);
  Matrix *y = matrix_init_empty(1, 10);
  int take = 36000;
  int indexes[take];
  for (int i = 0; i < take; i++) {
    indexes[i] = i;
  }
  double result = 0;
  double tmp_res = 0;
  for (int j = 0; j < 5; j++) {
    shuffle_array(indexes, take);
    for (int i = 0; i < take; i++) {
      X->data[0] = vectors->data[indexes[i]];
      y->data[0] = labels->data[indexes[i]];

      forward_pass(network, X, y);
      backward_pass(network, X, y);

      if (i % 32 == 0 || i == take - 1) {
        apply_derivation(network, 32.0, 0.1);
      }
    }

    for (int i = 0; i < 500; i++) {
      X->data[0] = vectors->data[indexes[i]];
      y->data[0] = labels->data[indexes[i]];

      forward_pass(network, X, y);
    }
    result = network->good / (double)(network->good + network->bad);

    printf("Iterations %d, %.2f\n", j, result * 100);
    fflush(stdout);

    network->good = 0;
    network->bad = 0;
  }

  return 0;
}
