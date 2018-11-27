#include "main.h"

#define INPUT_L 28 * 28
#define HIDDEN_L 300
#define OUTPUT_L 10

int main(int argc, char const *argv[]) {
  srand(42);

  Network *network = network_init(2);
  for (int i = 0; i < network->num_of_layers; i++) {
    network->layers[i] = layer_init(10, 10, 10, sigmoid, sigmoid_prime);
    weights_init(network->layers[i], initializer_GB);
  }

  Matrix *X = matrix_init(1, 11);
  for (int i = 1; i <= 11; i++) {
    X->data[0][i] = i;
  }

  forward_pass(network, X);
  return 0;
}
