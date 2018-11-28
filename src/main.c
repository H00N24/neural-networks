#include "main.h"

#define INPUT_L 28 * 28
#define HIDDEN_L 300
#define OUTPUT_L 10

int main(int argc, char const *argv[]) {
  srand(42);

  Matrix *vectors = matrix_init(60000, 1 + 28 * 28);
  load_data(vectors, "../MNIST_DATA/mnist_test_vectors.csv", 28 * 28, true,
            scaler, 255);

  Matrix *labels = matrix_init(60000, 10);
  load_data(vectors, "../MNIST_DATA/mnist_test_labels.csv", 1, false,
            one_hot_encoder, 0);
  // return 0;
  Network *network = network_init(2);
  network->layers[0] =
      layer_init(HIDDEN_L, INPUT_L, 10, sigmoid, sigmoid_prime);

  network->layers[1] =
      layer_init(OUTPUT_L, HIDDEN_L, 10, sigmoid, sigmoid_prime);

  for (int i = 0; i < network->num_of_layers; i++) {
    weights_init(network->layers[i], initializer_GB);
  }

  Matrix *X = matrix_init(1, 1 + 28 * 28);

  for (int i = 0; i < 2; i++) {
    X->data[0] = vectors->data[i];
    forward_pass(network, X);
  }

  return 0;
}
