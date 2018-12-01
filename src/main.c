#include "main.h"

#define INPUT_L 28 * 28
#define HIDDEN_L 300
#define OUTPUT_L 10

int main(int argc, char const *argv[]) {
  srand(42);

  Matrix *all_data = matrix_init(60000, 1 + INPUT_L, false);
  load_data(all_data, "../MNIST_DATA/mnist_train_vectors.csv", INPUT_L, true,
            scaler, 255.0);

  Matrix *all_labels = matrix_init(60000, 10, false);
  load_data(all_labels, "../MNIST_DATA/mnist_train_labels.csv", 1, false,
            one_hot_encoder, 1);

  Matrix *train_data, *train_labels, *test_data, *test_labels;

  train_test_split(all_data, all_labels, &train_data, &train_labels, &test_data,
                   &test_labels);

  Network *network = network_init(2);
  network->layers[0] = layer_init(HIDDEN_L, INPUT_L, 10, relu, relu_prime);

  network->layers[1] =
      layer_init(OUTPUT_L, HIDDEN_L, 10, sigmoid, sigmoid_prime);

  for (int i = 0; i < network->num_of_layers; i++) {
    weights_init(network->layers[i], initializer_GB);
  }

  Matrix *X = matrix_init_empty(1, 1 + 28 * 28);
  Matrix *y = matrix_init_empty(1, 10);

  double result = 0;
  for (int j = 0; j < 10; j++) {
    for (int i = 0; i < train_data->m; i++) {
      X->data[0] = train_data->data[i];
      y->data[0] = train_labels->data[i];

      forward_pass(network, X, y);
      backward_pass(network, X, y);

      if (i % 32 == 0 || i == train_data->m - 1) {
        apply_derivation(network, 32.0, 0.1);
      }
    }

    for (int i = 0; i < test_data->m; i++) {
      X->data[0] = test_data->data[i];
      y->data[0] = test_labels->data[i];

      forward_pass(network, X, y);
    }
    result = network->good / (double)(network->good + network->bad);

    printf("Epoch %d, %.2f\n", j + 1, result * 100);
    fflush(stdout);

    network->good = 0;
    network->bad = 0;
  }

  Matrix *final_data = matrix_init(10000, 1 + INPUT_L, false);
  load_data(final_data, "../MNIST_DATA/mnist_test_vectors.csv", INPUT_L, true,
            scaler, 255.0);

  Matrix *final_labels = matrix_init(10000, 10, false);
  load_data(final_labels, "../MNIST_DATA/mnist_test_labels.csv", 1, false,
            one_hot_encoder, 1);

  for (int i = 0; i < final_data->m; i++) {
    X->data[0] = final_data->data[i];
    y->data[0] = final_labels->data[i];

    forward_pass(network, X, y);
  }
  result = network->good / (double)(network->good + network->bad);

  printf("Final data %.2f\n", result * 100);
  fflush(stdout);
  return 0;
}
